#ifndef PARSE_H
#define PARSE_H

typedef struct {
    int argc;
    char** argv;
} Args;

Args parse(char* input);

void free_args(Args args);

#endif
