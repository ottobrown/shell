#ifndef PARSE_H
#define PARSE_H

#include <stdlib.h>

typedef struct {
    /// used to make sure all strings in `args` are `free`d
    size_t max;
    char** args;
} Args;

/// Input: the string given to the shell prompt
///
/// Output: input split up into arguments
Args parse(char* input);

void free_args(Args args);

#endif
