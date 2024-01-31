#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include "shell.h"

/// Creates a fork and runs the specified program with the specified arguments
///
/// return:
///    `0` if OK
///    `-1` if `fork` fails
///    `errno` if `execvp` fails
int run_command(Args args) {
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
