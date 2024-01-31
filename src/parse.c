#include <string.h>
#include <stdlib.h>

/// These chars can separate arguments to a command
const char SEPARATORS[] = " \n\t\r\f\v";

/// returns an array containing the arguments, where index `0` is the path
/// to the command to be run
char** parse(char* input, size_t* argc) {
    *argc = 1;
    char** argv = malloc(sizeof(char*));
    size_t i = 0;

    char* token = strtok(input, SEPARATORS);
    while (token != NULL) {
        if (i >= *argc) {
            *argc += 5;
            argv = realloc(argv, (*argc) * sizeof(char*));
        }

        argv[i] = strdup(token);

        token = strtok(NULL, SEPARATORS);
        i++;
    }
    if (i >= *argc) {
        *argc += 1;
        argv = realloc(argv, (*argc) * sizeof(char*));
    }

    argv[i] = NULL;

    free(token);

    return argv;
}
