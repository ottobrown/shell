#include <string.h>
#include <stdlib.h>
#include "parse.h"

/// These chars can separate arguments to a command
const char SEPARATORS[] = " \n\t\r\f\v";

Args parse(char* input) {
    Args args;

    size_t allocated = 3;
    size_t i = 0;

    args.argv = (char**) malloc(allocated * sizeof(char*));

    char* token = strtok(input, SEPARATORS);
    while (token != NULL) {
        if (i >= allocated) {
            allocated += 5;
            args.argv = realloc(args.argv, (allocated) * sizeof(char*));
        }

        args.argv[i] = strdup(token);

        token = strtok(NULL, SEPARATORS);
        i++;
    }
    if (i >= allocated) {
        allocated += 1;
        args.argv = realloc(args.argv, allocated * sizeof(char*));
    }

    args.argv[i] = NULL;
    args.argc = i+1;

    free(token);

    return args;
}

void free_args(Args args) {
    for(int i=0; i<args.argc; i++) free(args.argv[i]);
    free(args.argv);
}
