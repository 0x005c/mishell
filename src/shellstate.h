#ifndef MISH_SHELLSTATE_H
#define MISH_SHELLSTATE_H

#include <stdbool.h>

typedef struct ShellState {
  size_t cursor_pos_x;
  bool is_command_running;
} ShellState;

#endif

