#ifndef TOOLBOX_TYPE_H
#define TOOLBOX_TYPE_H

const char *BYTES_M_NAME = "toolbox.bytes";

#define checkbytes(L, i) (Bytes *)luaL_checkudata(L, i, BYTES_M_NAME)

typedef struct Bytes {
  int size;
  char *data;
} Bytes;

#endif
