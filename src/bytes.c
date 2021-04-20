#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

typedef struct Bytes {
  int size;
  char *data;
} Bytes;

static int newbytes(lua_State *L) {
  size_t nbytes = sizeof(Bytes) + (1) * sizeof(char);

  Bytes *b = (Bytes *)lua_newuserdata(L, nbytes);
  b->size = 1;

  luaL_getmetatable(L, "toolbox.bytes");
  lua_setmetatable(L, -2);

  return 1;
}

static int getsize(lua_State *L) {
  Bytes *b = (Bytes *)luaL_checkudata(L, 1, "toolbox.bytes");
  luaL_argcheck(L, b != NULL, 1, "`bytes` expected");
  lua_pushinteger(L, b->size);
  return 1;
}

static int tostring(lua_State *L) {
  Bytes *b = (Bytes *)luaL_checkudata(L, 1, "toolbox.bytes");

  lua_pushfstring(L, "bytes(%d)", b->size);

  return 1;
}

static const struct luaL_Reg byteslib_f[] = {
  {"new", newbytes},
  {NULL, NULL}
};

static const struct luaL_Reg byteslib_m[] = {
  {"__tostring", tostring},
  {"__len", getsize},
  {NULL, NULL}
};

int luaopen_toolbox_bytes(lua_State *L) {
  luaL_newmetatable(L, "toolbox.bytes");

  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");

  luaL_setfuncs(L, byteslib_m, 0);
  luaL_newlib(L, byteslib_f);

  return 1;
}
