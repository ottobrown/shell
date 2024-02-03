#ifndef PARSE_H
#define PARSE_H

typedef struct {
    int argc;
    char** argv;

    size_t* pipes;
    size_t num_pipes;
} Args;

Args parse(char* input);

void free_args(Args args);

#endif
