#ifndef TOOLBOX_BUFFER_H
#define TOOLBOX_BUFFER_H

const char *BUFFER_M_NAME = "toolbox.buffer";

#define checkbuffer(L, i) (Buffer *)luaL_checkudata(L, i, BUFFER_M_NAME)

typedef struct Buffer {
  int size;
  char *data;
} Buffer;

#endif
