#include <stdio.h>
#include <libgen.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "mish.h"
#include "core.h"
#include "mish_error.h"
#include "constants.h"
#include "builtin_functions.h"

int exec_command(Command *command) {
  if(strcmp(get_command_name(command), "exit") == 0) return builtin_exit();
  if(strcmp(get_command_name(command), "cd") == 0) return builtin_cd(command);
  S->is_command_running = true;
  pid_t pid = fork();
  if(pid == -1) {
    perror("non_builtin");
  }
  else if(pid == 0) {
    char *cname = get_command_name(command);
    char **cargs = get_command_args(command);
    if(execvp(cname, cargs) == -1) perror(cname);
    exit(EXIT_FAILURE);
  }
  else {
    int status;
    while(1) {
      waitpid(pid, &status, WUNTRACED);
      if(WIFEXITED(status) || WIFSIGNALED(status)) break;
    }
  }
  S->is_command_running = false;
  return 0;
}

void show_prompt() {
  char cwd[MISH_MAX_PATH_LENGTH];
  if(getcwd(cwd, MISH_MAX_PATH_LENGTH) == NULL) perror("mish");
  printf("%s", basename(cwd));
  printf("> ");
  fflush(stdout);
}

char* read_line(FILE *fp) {
  char *line = malloc(MISH_MAX_LINE_LENGTH+1);
  line[0] = '\0';
  int c;
  S->cursor_pos_x = 0;
  while(S->cursor_pos_x < MISH_MAX_LINE_LENGTH) {
    c = fgetc(fp);
    // detect ctrl-d
    if(c == 0x04) printf("\n"), builtin_exit();
    if(c == '\n' || c == '\r') break;
    if(c == '\t') {
      printf("\n");
      error_not_implemented("tab completion");
      break;
    }
    line[S->cursor_pos_x++] = c;
  }
  line[S->cursor_pos_x] = '\0';
  return line;
}

void interrupt() {
  printf("\n");
  S->cursor_pos_x = 0;
  if(!S->is_command_running) show_prompt();
}

void mish(FILE *fp) {
  while(1) {
    signal(SIGINT, interrupt);
    show_prompt();
    char *line = read_line(fp);
    Command *command = gen_command(line);
    if(command) exec_command(command);
    free(line); line = NULL;
    free_command(command);
    command = NULL;
  }
}

