#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <sys/wait.h>

#include "mish.h"
#include "core.h"
#include "constants.h"
#include "shellstate.h"
#include "builtin_functions.h"

ShellState* parse_args(int argc, char *argv[]) {
  ShellState *S = malloc(sizeof(ShellState));
  S->cursor_pos_x = 0;
  S->is_command_running = false;
  for(int i=1; i<argc; i++) {
    if(argv[i][0] == '-') {
      if(strcmp(argv[i++]+1, "c") == 0) S->command_mode = true;
      if(i<argc) S->command = argv[i];
      else {
        fprintf(stderr, "-c option requires command name\n");
        exit(1);
      }
    }
  }
  return S;
}

ShellState *S;

int main(int argc, char *argv[]) {
  S = parse_args(argc, argv);
  if(S->command_mode) {
    Command *command = gen_command(S->command);
    return exec_command(command);
  }
  else mish(stdin);
}

