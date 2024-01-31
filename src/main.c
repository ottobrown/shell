#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include "parse.h"

void print_cmd_error(int e) {
    switch (e) {
        case 0:
            return;
        case -1:
            fprintf(stderr, "Failed to create fork!\n");
            break;
        default:
            perror("");
    };
}

int main(void) {
    while (1) {
        printf("> ");

        size_t size = 30;
        char* s = malloc(size);
        getline(&s, &size, stdin);

        Args cmd_args = parse(s);

        int r = run_command(cmd_args);

        if (r) print_cmd_error(r);

        free(s);
        free_args(cmd_args);
    }

    return 0;
}

