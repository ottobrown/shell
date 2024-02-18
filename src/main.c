#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"
#include "escape.h"

int main(void) {
    while (1) {
        char* cwd = getcwd(NULL, 0);

        set_fg_color(RED);
        printf("%s> ", cwd);
        set_default_color();

        size_t size = 30;
        char* s = malloc(size);
        getline(&s, &size, stdin);

        char** cmd_args = parse(s);

        int r = run_command(cmd_args);

        free(s);
        free(cwd);
        free(cmd_args);
    }

    return 0;
}
