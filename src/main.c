#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include "shell.h"
#include "parse.h"
#include "escape.h"

void print_result(enum ShellResult r) {
    switch (r) {
        case OK:
            return;
        case EXECVP_RETURNED:
            perror("execvp returned");
            break;
        case FORK_FAILED:
            perror("fork failed");
            break;
        default:
            assert(0);
            break;
    }
}

int main(void) {
    assert(printf("asserts enabled\n") == 16);

    while (1) {
        char* cwd = getcwd(NULL, 0);

        set_fg_color(RED);
        printf("%s> ", cwd);
        set_default_color();

        size_t size = 30;
        char* s = malloc(size);
        getline(&s, &size, stdin);

        Args cmd_args = parse(s);

        enum ShellResult r = run_command(cmd_args.args);
        print_result(r);

        free(s);
        free(cwd);
        free_args(cmd_args);
    }

    return 0;
}
