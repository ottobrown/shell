#ifndef LINE_BUFFER_H
#define LINE_BUFFER_H

#include<stdbool.h>

struct LineBuffer {
    char* line;
    /// The number of bytes allocated to `line`
    size_t allocated_size;
    /// The index on `line` at which the `\0` terminator is located
    size_t terminator;
};

struct LineBuffer init_buffer();

/// Returns `true` if the buffer is ready to be `parse`d
bool handle_char(struct LineBuffer* buf, char c);

#endif
