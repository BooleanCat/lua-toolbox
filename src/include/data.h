#ifndef TOOLBOX_DATA_H
#define TOOLBOX_DATA_H

const char *DATA_M_NAME = "toolbox.data";

#define toolbox_checkdata(L, i) (Data *)luaL_checkudata(L, i, DATA_M_NAME)

typedef struct Data {
  size_t size;
  char *data;
} Data;

#endif
