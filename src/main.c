#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <assert.h>
#include "shell.h"
#include "parse.h"
#include "escape.h"

static struct termios ORIGINAL_TERM;

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

void handle_char(char c, char* line, size_t* size, size_t* i) {
    // TODO: handle arrow keys, backspace

    putchar(c);
    fflush(stdout);
    if (*i+1 >= *size) {
        *size *= 2;
        line = realloc(line, *size);
    }

    line[*i] = c;
    line[*i+1] = '\0';
    *i = *i + 1;
}

void restore_original_term() {
    tcsetattr(STDIN_FILENO, TCSANOW, &ORIGINAL_TERM);
}

int main(void) {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    ORIGINAL_TERM = term;

    assert(printf("asserts enabled\n") == 16);

    while (1) {
        term.c_lflag &= ~(ECHO | ICANON);
        tcsetattr(STDIN_FILENO, TCSANOW, &term);

        char* cwd = getcwd(NULL, 0);

        set_fg_color(RED);
        printf("%s> ", cwd);
        set_default_color();

        size_t size = 30;
        size_t idx = 0;
        char* line = malloc(size);
        char ch = '\0';
        while (ch != '\n') {
            if (read(STDIN_FILENO, &ch, 1) == 1) {
                handle_char(ch, line, &size, &idx);
            }
        }

        Args cmd_args = parse(line);

        restore_original_term();

        enum ShellResult r = run_command(cmd_args.args);
        print_result(r);

        free(line);
        free(cwd);
        free_args(cmd_args);
    }

    return 0;
}
