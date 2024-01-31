#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include "parse.h"

int main(void) {
    while (1) {
        printf("> ");

        size_t size = 30;
        char* s = malloc(size);
        getline(&s, &size, stdin);

        size_t arg_count;
        char** args = parse(s, &arg_count);

        run_command(args);

        for(size_t i = 0; i<arg_count; i++) free(args[i]);
        free(s);
        free(args);
    }

    return 0;
}

