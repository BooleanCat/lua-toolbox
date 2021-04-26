#ifndef TOOLBOX_TYPES_H
#define TOOLBOX_TYPES_H

const char *BYTES_METATABLE_HANDLE = "toolbox.types.bytes";

#define checkbytes(L, i) (Bytes *)luaL_checkudata(L, i, BYTES_METATABLE_HANDLE)

typedef struct Bytes {
  int size;
  char *data;
} Bytes;

#endif
