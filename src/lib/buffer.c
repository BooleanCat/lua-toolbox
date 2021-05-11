#include <lualib.h>
#include <lauxlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "buffer.h"
#include "data.h"

static Buffer * _buffer_new(lua_State *L, const char *data, size_t size) {
  Buffer *buffer = (Buffer *)lua_newuserdata(L, sizeof(Buffer));
  buffer->read_cursor = 0;
  buffer->write_cursor = size;
  buffer->capacity = MAX(BUFFER_MIN_CAPACITY, size);

  buffer->data = (char *)malloc(sizeof(char) * size);
  buffer->data = memcpy((void *)buffer->data, (void *)data, size);

  return buffer;
}

static int buffer_new(lua_State *L) {
  Buffer *buffer;

  if (lua_gettop(L) == 0) {
    buffer = _buffer_new(L, NULL, 0);
  } else {
    Data *data = toolbox_checkdata(L, 1);
    buffer = _buffer_new(L, data->data, data->size);
  }

  luaL_getmetatable(L, BUFFER_M_NAME);
  lua_setmetatable(L, -2);

  return 1;
}

static int buffer__len(lua_State *L) {
  Buffer *buffer = toolbox_checkbuffer(L, 1);

  lua_pushinteger(L, 0);
  return 1;
}

static int buffer__tostring(lua_State *L) {
  Buffer *buffer = toolbox_checkbuffer(L, 1);

  lua_pushfstring(
    L,
    "toolbox.buffer<%d, %d>",
    buffer->write_cursor - buffer->read_cursor,
    buffer->capacity
  );
  return 1;
}

static int buffer__gc(lua_State *L) {
  Buffer *buffer = toolbox_checkbuffer(L, 1);

  free((void *)buffer->data);
  buffer->data = NULL;

  return 0;
}

static int buffer__tbread(lua_State *L) {
  Buffer *buffer = toolbox_checkbuffer(L, 1);
  Data *data = toolbox_checkdata(L, 2);

  lua_pushinteger(L, 0);

  return 1;
}

static int buffer__tbwrite(lua_State *L) {
  Buffer *buffer = toolbox_checkbuffer(L, 1);
  Data *data = toolbox_checkdata(L, 2);

  memcpy(
    (void *)(buffer->data + buffer->write_cursor),
    (void *)data->data,
    data->size
  );

  buffer->write_cursor += data->size;

  lua_pushinteger(L, data->size);

  return 1;
}

static int buffer_data(lua_State *L) {
  Buffer *buffer = toolbox_checkbuffer(L, 1);

  Data *data = (Data *)lua_newuserdata(L, sizeof(Data));
  data->reference = true;
  data->data = buffer->data + buffer->read_cursor;
  data->size = buffer->write_cursor - buffer->read_cursor;

  luaL_getmetatable(L, DATA_M_NAME);
  lua_setmetatable(L, -2);

  return 1;
}

static int buffer_reset(lua_State *L) {
  Buffer *buffer = toolbox_checkbuffer(L, 1);

  return 0;
}

static int buffer_cap(lua_State *L) {
  Buffer *buffer = toolbox_checkbuffer(L, 1);

  lua_pushinteger(L, buffer->capacity);
  return 1;
}

static const struct luaL_Reg bufferlib_f[] = {
  {"new", buffer_new},
  {NULL, NULL}
};

static const struct luaL_Reg bufferlib_m[] = {
  {"__len", buffer__len},
  {"__tostring", buffer__tostring},
  {"__tbread", buffer__tbread},
  {"__tbwrite", buffer__tbwrite},
  {"data", buffer_data},
  {"reset", buffer_reset},
  {"cap", buffer_cap},
  {NULL, NULL}
};

int luaopen_toolbox_buffer(lua_State *L) {
  luaL_newmetatable(L, BUFFER_M_NAME);

  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");

  luaL_setfuncs(L, bufferlib_m, 0);
  luaL_newlib(L, bufferlib_f);

  return 1;
}
