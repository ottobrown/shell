#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include "shell.h"
#include "builtin.h"

/// Finds a matching index on `BUILTIN_NAMES`
/// or `-1` if none exists
int find_builtin(char* name) {
    for(int i=0; BUILTIN_NAMES[i] != NULL; i++) {
        if (!strcmp(BUILTIN_NAMES[i], name)) {
            return i;
        }
    }

    return -1;
}

int run_direct(int argc, char** argv) {
    // Do nothing if no arguments are given
    if (argc == 0) return 0;

    // search for builtins first
    int builtin_i = find_builtin(argv[0]);
    if (builtin_i >= 0) {
        (BUILTIN_FUNCTIONS[builtin_i])(argc, argv);
        return 0;
    }

    int rc = fork();

    if (rc < 0) { /* Our `fork()` failed */
        return 1;
    }
    if (rc == 0) { /* We are in the child process */
        execvp(argv[0], argv);

        // (if `exexvp` returns, an error has occured)
        _exit(errno);
    }
    else { /* We are in the parent process */
        int status;
        (void) wait(&status);

        if (status && WIFEXITED(status)) {
            int real_status = WEXITSTATUS(status);
            errno = real_status;
            return -2;
        }
        return 0;
    }
}

/// This will mangle the `Args` and render it unusable
///
/// return:
///    `0` if OK
///    `-1` if `fork` fails
///    `-2` if `execvp` fails
int run_command(Args args) {
    return run_direct(args.argc, args.argv);
}
