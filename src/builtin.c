#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void builtin_cd(int argc, char** argv) {
    // do nothing if no arg provided
    if (argc == 0) return;

    if (chdir(argv[1]) == -1) {
        perror("cd failed");
    }
}

void builtin_exit(int argc, char** argv) {
    (void) argc;
    (void) argv;
    
    int status = 0;
    printf("exiting with status %d\n", status);

    exit(status);
}
