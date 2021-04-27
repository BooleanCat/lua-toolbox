#ifndef TOOLBOX_BYTES_H
#define TOOLBOX_BYTES_H

const char *BUFFER_METATABLE_HANDLE = "toolbox.bytes.buffer";

#define checkbuffer(L, i) (Buffer *)luaL_checkudata(L, i, BUFFER_METATABLE_HANDLE)

typedef struct Buffer {
  int size;
  char *data;
} Buffer;

#endif
