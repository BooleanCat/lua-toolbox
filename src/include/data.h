#ifndef TOOLBOX_DATA_H
#define TOOLBOX_DATA_H

const char *DATA_M_NAME = "toolbox.data";
const char *DATASLICE_M_NAME = "toolbox.dataslice";

#define toolbox_checkdata(L, i) (Data *)luaL_checkudata(L, i, DATA_M_NAME)
#define toolbox_checkdataslice(L, i) (DataSlice *)luaL_checkudata(L, i, DATASLICE_M_NAME)

typedef struct Data {
  size_t size;
  char *data;
} Data;

typedef struct DataSlice {
  size_t offset;
  size_t size;
  Data *data;
} DataSlice;

#endif
