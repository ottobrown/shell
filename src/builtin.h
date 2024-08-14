#ifndef BUILTIN_H
#define BUILTIN_H

#include <stdlib.h>

void builtin_exit(int argc, char** argv);
void builtin_cd(int argc, char** argv);

static const char* BUILTIN_NAMES[] = { "exit", "cd", NULL };
static void (*BUILTIN_FUNCTIONS[])(int, char**) = { &builtin_exit, &builtin_cd };

#endif
