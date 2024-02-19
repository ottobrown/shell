#include <string.h>
#include <stdlib.h>
#include "parse.h"

/// These chars can separate arguments to a command
const char SEPARATORS[] = " \n\t\r\f\v";

Args parse(char* input) {
    // TODO: parse quote marks
    Args args;

    size_t allocated = 3;
    size_t i = 0;

    args.args = (char**) malloc(allocated * sizeof(char*));
    
    char* token = strtok(input, SEPARATORS);
    while (token != NULL) {
        if (i >= allocated) {
            allocated += 5;
            args.args = realloc(args.args, (allocated) * sizeof(char*));
        }

        args.args[i] = strdup(token);
        
        token = strtok(NULL, SEPARATORS);
        i++;
    }
    if (i >= allocated) {
        allocated += 1;
        args.args = realloc(args.args, allocated * sizeof(char*));
    }

    args.args[i] = NULL;
    // This does not include the `NULL` the end, which does not have to be `free`d
    args.max = i;

    free(token);

    return args;
}

void free_args(Args args) {
    for(size_t i=0; i<args.max; i++) free(args.args[i]);
    free(args.args);
}
