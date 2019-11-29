#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <sys/wait.h>

#include "core.h"
#include "constants.h"
#include "shellstate.h"
#include "builtin_functions.h"

ShellState* parse_args(int argc, char *argv[]) {
  ShellState *S = malloc(sizeof(ShellState));
  return S;
}

ShellState *S;

void on_receive_SIGINT(int sig_num) {
  signal(SIGINT, on_receive_SIGINT);
  printf("\n");
  main_loop(S, stdin);
}

struct termios t;
int main(int argc, char *argv[]) {
  signal(SIGINT, on_receive_SIGINT);
  S = parse_args(argc, argv);

  tcgetattr(STDIN_FILENO, &t);
  t.c_lflag &= ~ICANON;
  tcsetattr(STDIN_FILENO, TCSANOW, &t);
  main_loop(S, stdin);
}

