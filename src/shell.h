#ifndef SHELL_H
#define SHELL_H

enum ShellResult {
    OK = 0,
    EXECVP_RETURNED,
    FORK_FAILED,
};

/// Input: list of arguments terminated by `NULL`
///
/// Example input: ["grep", "-ir", "TODO", "src/", "|", "less", NULL]
enum ShellResult run_command(char** args);

#endif
