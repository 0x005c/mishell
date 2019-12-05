#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "mish_error.h"
#include "command.h"
#include "constants.h"

char* get_command_name(Command *command) {
  return command->args[0];
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

struct ParseState {
  bool is_redirect_to, is_redirect_from;
} PS = {.is_redirect_to = false, .is_redirect_from = false};

Command* gen_empty_command() {
  Command *command = malloc(sizeof(Command));
  command->args = malloc(sizeof(char*)*MISH_MAX_ARG_COUNT);
  command->redirect_to = NULL;
  command->redirect_from = NULL;
  return command;
}

Command* gen_command(const char *line) {
  int i=0, j=0, args_pos=0;
  Command *command = gen_empty_command();
  while(line[i] != '\0') {
    if(line[i] == '>') {
      PS.is_redirect_to = true;
      i++;
      /* TODO: handle '>>'
      if(line[i] == '>') {
      }
       */
      continue;
    }
    if(line[i] == '<') {
      PS.is_redirect_from = true;
      i++;
      continue;
    }

    while(is_space(line[i])) {
      i++;
    }
    j = i;
    while(!is_space(line[i])) {
      if(line[i] == '\0'
          || line[i] == '>'
          || line[i] == '<') break;
      else i++;
    }
    if(i != j) {
      char *word = malloc(i-j+1);
      strncpy(word, line+j, i-j);
      word[i-j] = '\0';

      if(PS.is_redirect_to || PS.is_redirect_from) {
        if(PS.is_redirect_to) {
          command->redirect_to = word;
          PS.is_redirect_to = false;
        }
        if(PS.is_redirect_from) {
          command->redirect_from = word;
          PS.is_redirect_from = false;
        }
      }
      else command->args[args_pos++] = word;
    }
  }
  command->args[args_pos] = NULL;

  if(command->args[0]) return command;
  else {
    free_command(command);
    return NULL;
  }
}

void free_command(Command *command) {
  for(int i=0; command->args[i] != NULL; i++) free(command->args[i]);
  free(command->args);
  free(command->redirect_to);
  free(command->redirect_from);
  free(command);
}
