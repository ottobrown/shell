#include <stdlib.h>
#include <stdio.h>

void builtin_exit(int argc, char** argv) {
    (void) argc;
    (void) argv;
    
    int status = 0;
    printf("exiting with status %d\n", status);

    exit(status);
}
