#include <unistd.h>
#include <sys/wait.h>

/// Creates a fork and runs the specified program with the specified arguments
/// `args[0]` is the path to the command to be run
int run_command(char** args) {
    int rc = fork();

    if (rc < 0) { /* Our `fork()` failed */
        return 1;
    }
    if (rc == 0) { /* We are in the child process */
        execvp(args[0], args);

        // (if `exexvp` returns, an error has occured)
        return 2;
    }
    else { /* We are in the parent process */
        (void) wait(NULL);
    }

    return 0;
}
