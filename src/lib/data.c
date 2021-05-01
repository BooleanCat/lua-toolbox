#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "data.h"

static int new_from_integer(lua_State *L, size_t size) {
  Data *data = (Data *)lua_newuserdata(L, sizeof(Data));
  data->size = size;
  data->data = (char *)malloc(sizeof(char) * size);

  memset(data->data, 0, sizeof(char) * data->size);

  luaL_getmetatable(L, DATA_M_NAME);
  lua_setmetatable(L, -2);

  return 1;
}

static int new_from_string(lua_State *L, size_t size, const char *str) {
  Data *data = (Data *)lua_newuserdata(L, sizeof(Data));
  data->size = size;
  data->data = (char *)malloc(sizeof(char) * size);

  memcpy((void *)data->data, (void *)str, sizeof(char) * size);

  luaL_getmetatable(L, DATA_M_NAME);
  lua_setmetatable(L, -2);

  return 1;
}

static int new(lua_State *L) {
  if (lua_gettop(L) == 0) {
    return new_from_integer(L, 0);
  }

  if (lua_isinteger(L, 1)) {
    return new_from_integer(L, luaL_checkinteger(L, 1));
  }

  if (lua_isstring(L, 1)) {
    size_t size;
    const char *str = luaL_checklstring(L, 1, &size);
    return new_from_string(L, size, str);
  }

  luaL_argexpected(L, false, 1, "string or integer");
}

static const struct luaL_Reg datalib_f[] = {
  {"new", new},
  {NULL, NULL}
};

static int __eq(lua_State *L) {
  Data *a = toolbox_checkdata(L, 1);
  Data *b = toolbox_checkdata(L, 2);

  if (a->size != b-> size) {
    lua_pushboolean(L, false);
    return 1;
  }

  lua_pushboolean(L, memcmp(
    a->data,
    b->data,
    sizeof(char) * a->size
  ) == 0);
  return 1;
}

static int __tostring(lua_State *L) {
  Data *data = toolbox_checkdata(L, 1);

  if (data->size == 0) {
    lua_pushstring(L, "[]");
    return 1;
  }

  luaL_Buffer buffer;

  // Number of characters to write
  size_t size = sizeof(char) * (2 + 3 * data->size - 1);

  luaL_buffinitsize(L, &buffer, size);
  luaL_addchar(&buffer, '[');

  char *addr = luaL_prepbuffsize(&buffer, size - 1);

  for (size_t i = 0; i < data->size; i++) {
    sprintf(addr, "%02X ", data->data[i]);
    addr += 3;
  }

  luaL_addsize(&buffer, size - 2);
  luaL_addchar(&buffer, ']');

  luaL_pushresult(&buffer);

  return 1;
}

static int data__len(lua_State *L) {
  Data *data = toolbox_checkdata(L, 1);

  lua_pushinteger(L, data->size);
  return 1;
}

static int __concat(lua_State *L) {
  Data *a = toolbox_checkdata(L, 1);
  Data *b = toolbox_checkdata(L, 2);

  size_t size = a->size + b->size;

  Data *data = (Data *)lua_newuserdata(L, sizeof(Data));
  data->size = size;
  data->data = (char *)malloc(sizeof(char) * size);

  memcpy(
    (void *)data->data,
    (void *)a->data,
    sizeof(char) * a->size
  );

  memcpy(
    (void *)data->data + a->size,
    (void *)b->data,
    sizeof(char) * b->size
  );

  luaL_getmetatable(L, DATA_M_NAME);
  lua_setmetatable(L, -2);

  return 1;
}

static int __gc(lua_State *L) {
  Data *data = toolbox_checkdata(L, 1);

  free((void *)data->data);
  data->data = NULL;

  return 0;
}

static const struct luaL_Reg datalib_m[] = {
  {"__eq", __eq},
  {"__tostring", __tostring},
  {"__len", data__len},
  {"__concat", __concat},
  {"__gc", __gc},
  {NULL, NULL}
};

int luaopen_toolbox_data(lua_State *L) {
  luaL_newmetatable(L, DATA_M_NAME);

  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");

  luaL_setfuncs(L, datalib_m, 0);

  luaL_newlib(L, datalib_f);

  return 1;
}
