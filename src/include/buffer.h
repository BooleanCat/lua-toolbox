#ifndef TOOLBOX_BUFFER_H
#define TOOLBOX_BUFFER_H

const char *BUFFER_M_NAME = "toolbox.buffer";

#define checkbuffer(L, i) (Buffer *)luaL_checkudata(L, i, BUFFER_M_NAME)

#define MIN(a, b) a > b ? b : a

typedef struct Buffer {
  int size;
  int cursor;
  char *data;
} Buffer;

#endif
