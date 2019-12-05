#ifndef MISH_COMMAND_H
#define MISH_COMMAND_H

typedef struct Command {
  char *redirect_to;
  char *redirect_from;
  char **args;
} Command;

char* get_command_name(Command *command);
char** get_command_args(Command *command);
int get_command_argc(Command *command);
Command* gen_command(const char *line);

void free_command(Command *command);

#endif

