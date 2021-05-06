#include <lualib.h>
#include <lauxlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "buffer.h"

static int buffer_new(lua_State *L) {
  Buffer *buffer = (Buffer *)lua_newuserdata(L, sizeof(Buffer));
  buffer->capacity = BUFFER_MIN_CAPACITY;
  buffer->read_cursor = 0;
  buffer->write_cursor = 0;
  buffer->data = (char *)malloc(sizeof(char) * BUFFER_MIN_CAPACITY);

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

  return 0;
}

static int buffer__tbwrite(lua_State *L) {
  Buffer *buffer = toolbox_checkbuffer(L, 1);

  return 0;
}

static int buffer_data(lua_State *L) {
  Buffer *buffer = toolbox_checkbuffer(L, 1);

  return 0;
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
