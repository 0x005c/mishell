#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "mish_error.h"
#include "command.h"
#include "constants.h"

char* get_command_name(Command *command) {
  return command->name;
}

char** get_command_args(Command *command) {
  return command->args;
}

int get_command_argc(Command *command) {
  int i = 0;
  while(command->args[i] != NULL) i++;
  return i;
}

bool is_space(char c) {
  if(c == ' ') return true;
  else return false;
}

Command* gen_command(const char *line) {
  int i=0, j=0, args_pos=0;
  char** args = malloc(sizeof(char*)*MISH_MAX_ARG_COUNT);
  while(line[i] != '\0') {
    while(is_space(line[i])) {
      i++;
    }
    j = i;
    while(!is_space(line[i])) {
      if(line[i] == '\0') break;
      else i++;
    }
    if(i != j) {
      char *word = malloc(i-j+1);
      strncpy(word, line+j, i-j);
      args[args_pos++] = word;
    }
  }
  args[args_pos] = NULL;

  if(args[0]) {
    Command *command = malloc(sizeof(Command));
    command->name = args[0];
    command->args = args;
    return command;
  }
  else {
    return NULL;
  }
}

