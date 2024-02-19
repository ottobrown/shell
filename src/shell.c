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

enum ShellResult run_direct(int argc, char** argv) {
    // Do nothing if no arguments are given
    if (argc == 0) return OK;

    // search for builtins first
    int builtin_i = find_builtin(argv[0]);
    if (builtin_i >= 0) {
        (BUILTIN_FUNCTIONS[builtin_i])(argc, argv);
        return OK;
    }

    int rc = fork();

    if (rc < 0) { /* Our `fork()` failed */
        return FORK_FAILED;
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
            return EXECVP_RETURNED;
        }
        return OK;
    }
}

enum ShellResult run_command(char** args) {
    int i = 0;
    while(1) {
        if (args[i] == NULL) {
            return run_direct(i, args);
        }

        if( !strcmp(args[i], ";") ) {
            // Run the command to the left of the `;`
            args[i] = NULL;
            enum ShellResult left = run_direct(i, args);

            // If the shell fails to run the first command, return.
            // It doesn't matter if the program itself succeeds or fails.
            if (left != OK) return left;

            return run_command(args + i + 1);
        }

        // TODO: pipe

        i++;
    }

    return OK;
}
