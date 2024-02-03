#include <string.h>
#include <stdlib.h>
#include "parse.h"

/// These chars can separate arguments to a command
const char SEPARATORS[] = " \n\t\r\f\v";

/// Splits the given string with the following separators:
/// `\n`, `\t`, `\r`, `\f`, `\v`
/// and places a NULL at the end
Args parse(char* input) {
    Args args;

    size_t allocated = 3;
    size_t i = 0;

    args.argv = (char**) malloc(allocated * sizeof(char*));
    args.num_pipes = 1;
    args.pipes = (size_t*) malloc(args.num_pipes * sizeof(size_t));
    
    char* token = strtok(input, SEPARATORS);
    while (token != NULL) {
        if (i >= allocated) {
            allocated += 5;
            args.argv = realloc(args.argv, (allocated) * sizeof(char*));
        }

        args.argv[i] = strdup(token);
        
        if (!strcmp(token, "|")) {
            args.pipes[args.num_pipes - 1] = i;

            args.num_pipes ++;
            args.pipes = realloc(args.pipes, args.num_pipes * sizeof(size_t));
        }

        token = strtok(NULL, SEPARATORS);
        i++;
    }
    if (i >= allocated) {
        allocated += 1;
        args.argv = realloc(args.argv, allocated * sizeof(char*));
    }

    args.argv[i] = NULL;
    // This does not include the `NULL` the end
    args.argc = i;

    free(token);

    return args;
}

void free_args(Args args) {
    for(int i=0; i<args.argc; i++) free(args.argv[i]);
    free(args.argv);
    free(args.pipes);
}
