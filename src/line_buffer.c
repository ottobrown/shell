#include <stdlib.h>
#include <stdio.h>
#include "line_buffer.h"

struct LineBuffer init_buffer() {
    struct LineBuffer buffer;

    buffer.allocated_size = 30;
    buffer.terminator = 0;
    buffer.line = malloc(buffer.allocated_size);
    buffer.line[0] = '\0';

    return buffer;
}

bool handle_char(struct LineBuffer* buf, char c) {
    // TODO: handle arrow keys, backspace

    putchar(c);
    fflush(stdout);

    if (c == '\n')
        return true;

    buf->terminator ++;

    if (buf->terminator >= buf->allocated_size) {
        buf->allocated_size *= 2;
        buf->line = realloc(buf->line, buf->allocated_size);
    }

    buf->line[buf->terminator-1] = c;
    buf->line[buf->terminator] = '\0';

    return false;
}

