#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <assert.h>
#include "shell.h"
#include "parse.h"
#include "escape.h"
#include "line_buffer.h"

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

        struct LineBuffer line_buf = init_buffer();
        char ch = '\0';
        while (1) {
            if (read(STDIN_FILENO, &ch, 1) == 1) {
                if (handle_char(&line_buf, ch)) {
                    break;
                }
            }
        }

        Args cmd_args = parse(line_buf.line);

        restore_original_term();

        enum ShellResult r = run_command(cmd_args.args);
        print_result(r);

        free(line_buf.line);
        free(cwd);
        free_args(cmd_args);
    }

    return 0;
}
