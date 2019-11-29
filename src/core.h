#ifndef MISH_CORE_H
#define MISH_CORE_H

#include "command.h"
#include  "shellstate.h"

int exec_command(Command *command);
void main_loop(ShellState *S, FILE *fp);

#endif

