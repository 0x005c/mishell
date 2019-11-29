#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "mish_error.h"
#include "command.h"
#include "builtin_functions.h"

int builtin_cd(Command *command) {
  if(get_command_argc(command) > 2) {
    error_too_many_arguments("cd");
    return -1;
  }
  else if(get_command_argc(command) < 2) {
    error_too_few_arguments("cd");
    return -1;
  }
  if(chdir(command->args[1]) < 0) {
    perror("cd");
    return -1;
  }
  return 0;
}

int builtin_exit() {
  printf("exit.\n");
  exit(0);
}

