#ifndef TOOLBOX_BUFFER_H
#define TOOLBOX_BUFFER_H

const char *BUFFER_M_NAME = "toolbox.buffer";

#define toolbox_checkbuffer(L, i) (Buffer *)luaL_checkudata(L, i, BUFFER_M_NAME)

#define MIN(a, b) a > b ? b : a
#define MAX(a, b) a > b ? a : b

#define BUFFER_MIN_CAPACITY 50

typedef struct Buffer {
  size_t capacity;
  size_t write_cursor;
  size_t read_cursor;
  char *data;
} Buffer;

#endif
