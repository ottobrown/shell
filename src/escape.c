#include <stdio.h>
#include "escape.h"

void set_fg_color(enum ForegroundColor color) {
    printf("\e[%dm", color);
    fflush(stdout);
}

void set_default_color() {
    printf("\e[%dm", DEFAULT_COLOR);
    fflush(stdout);
}
