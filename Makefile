CC = gcc
CFLAGS_COMMON = -Wall -Wextra

CFLAGS_DEBUG = -g -O0 -UNDEBUG
LDFLAGS_DEBUG =

CFLAGS_RELEASE = -O3 -DNDEBUG
LDFLAGS_RELEASE =

SRCS = src/main.c src/shell.c src/parse.c src/builtin.c
OBJS = $(SRCS:.c=.o)
TARGET = shell

.PHONY: all debug release clean

all: debug

# Debug target
debug: CFLAGS += $(CFLAGS_COMMON) $(CFLAGS_DEBUG)
debug: LDFLAGS += $(LDFLAGS_DEBUG)
debug: $(TARGET)

# Release target
release: CFLAGS += $(CFLAGS_COMMON) $(CFLAGS_RELEASE)
release: LDFLAGS += $(LDFLAGS_RELEASE)
release: $(TARGET)

# Compile rule
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link rule
$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
