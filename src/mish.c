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
  return S;
}

ShellState *S;

struct termios t;
int main(int argc, char *argv[]) {
  S = parse_args(argc, argv);

  tcgetattr(STDIN_FILENO, &t);
  t.c_lflag &= ~ICANON;
  tcsetattr(STDIN_FILENO, TCSANOW, &t);
  mish(stdin);
}

