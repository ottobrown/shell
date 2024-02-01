#ifndef BUILTIN_H
#define BUILTIN_H

void builtin_exit(int argc, char** argv);

char *const BUILTIN_NAMES[] = { "exit", NULL };
void (*BUILTIN_FUNCTIONS[])(int, char**) = { &builtin_exit };

#endif
