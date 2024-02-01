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
            //printf("found builtin %d\n", i);
            return i;
        }
    }

    return -1;
}

/// Creates a fork and runs the specified program with the specified arguments
///
/// return:
///    `0` if OK
///    `-1` if `fork` fails
///    `errno` if `execvp` fails
int run_command(Args args) {
    // search for builtins first
    int builtin_i = find_builtin(args.argv[0]);
    if (builtin_i >= 0) {
        (BUILTIN_FUNCTIONS[builtin_i])(args.argc, args.argv);
        return 0;
    }

    // search for builtins first
    int rc = fork();

    if (rc < 0) { /* Our `fork()` failed */
        return 1;
    }
    if (rc == 0) { /* We are in the child process */
        execvp(args.argv[0], args.argv);

        // (if `exexvp` returns, an error has occured)
        return errno;
    }
    else { /* We are in the parent process */
        (void) wait(NULL);
    }

    return 0;
}
