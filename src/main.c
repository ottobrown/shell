#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"
#include "parse.h"
#include "escape.h"

void print_cmd_error(int e) {
    switch (e) {
        case 0:
            return;
        case -1:
            perror("fork failed");
            break;
        case -2:
            perror("execvp exited");
            break;
        default:
            fprintf(stderr, "unknown error code\n");
            break;
    };
}

int main(void) {
    while (1) {
        char* cwd = getcwd(NULL, 0);

        set_fg_color(RED);
        printf("%s> ", cwd);
        set_default_color();

        size_t size = 30;
        char* s = malloc(size);
        getline(&s, &size, stdin);

        Args cmd_args = parse(s);

        int r = run_command(cmd_args);

        if (r) print_cmd_error(r);

        free(s);
        free(cwd);
        free_args(cmd_args);
    }

    return 0;
}
