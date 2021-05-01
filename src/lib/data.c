#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "data.h"

static int new(lua_State *L) {
  Data *data = (Data *)lua_newuserdata(L, sizeof(Data));
  data->size = 0;
  data->data = NULL;

  luaL_getmetatable(L, DATA_M_NAME);
  lua_setmetatable(L, -2);

  return 1;
}

static int __eq(lua_State *L) {
  Data *data = toolbox_checkdata(L, 1);
  return 0;
}

static int __tostring(lua_State *L) {
  Data *data = toolbox_checkdata(L, 1);
  return 0;
}

static int __len(lua_State *L) {
  Data *data = toolbox_checkdata(L, 1);
  return 0;
}

static int __concat(lua_State *L) {
  Data *data = toolbox_checkdata(L, 1);
  return 0;
}

static int slice(lua_State *L) {
  Data *data = toolbox_checkdata(L, 1);
  size_t offset = luaL_checkinteger(L, 2);
  size_t size = luaL_checkinteger(L, 3);
  return 0;
}

static const struct luaL_Reg datalib_f[] = {
  {"new", new},
  {"slice", slice},
  {NULL, NULL}
};

static const struct luaL_Reg datalib_m[] = {
  {"__eq", __eq},
  {"__tostring", __tostring},
  {"__len", __len},
  {"__concat", __concat},
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
