#include <stdio.h>
#include <error.h>
#include <errno.h>

#include "error.h"

void error_not_implemented(const char *name) {
  error(0, ENOSYS, "%s", name);
}

void error_too_many_arguments(const char *name) {
  fprintf(stderr, "%s: too many arguments\n", name);
}

void error_too_few_arguments(const char *name) {
  fprintf(stderr, "%s: too few arguments\n", name);
}

