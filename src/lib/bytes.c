#include <lualib.h>
#include <lauxlib.h>

static int newbuffer(lua_State *L) {
  lua_pushinteger(L, 1);

  return 1;
}

static const struct luaL_Reg byteslib_f[] = {
  {"buffer", newbuffer},
  {NULL, NULL}
};

int luaopen_toolbox_bytes(lua_State *L) {
  luaL_newlib(L, byteslib_f);

  return 1;
}
