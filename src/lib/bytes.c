#include <lualib.h>
#include <lauxlib.h>
#include "bytes.h"

static int newbuffer(lua_State *L) {
  Buffer *b = (Buffer *)lua_newuserdata(L, sizeof(Buffer));

  luaL_getmetatable(L, BUFFER_METATABLE_HANDLE);
  lua_setmetatable(L, -2);

  return 1;
}

static int getsize(lua_State *L) {
  Buffer *b = checkbuffer(L, 1);
  luaL_argcheck(L, b != NULL, 1, "`buffer` expected");
  lua_pushinteger(L, 0);
  return 1;
}

static const struct luaL_Reg byteslib_f[] = {
  {"buffer", newbuffer},
  {NULL, NULL}
};

static const struct luaL_Reg bufferlib_m[] = {
  {"__len", getsize},
  {NULL, NULL}
};

int luaopen_toolbox_bytes(lua_State *L) {
  luaL_newmetatable(L, BUFFER_METATABLE_HANDLE);

  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");

  luaL_setfuncs(L, bufferlib_m, 0);
  luaL_newlib(L, byteslib_f);

  return 1;
}
