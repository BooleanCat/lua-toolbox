#include <string.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

typedef struct Bytes {
  int size;
  char *data;
} Bytes;

static int newbytesempty(lua_State *L) {
  Bytes *b = (Bytes *)lua_newuserdata(L, sizeof(Bytes));
  b->size = 0;
  b->data = NULL;

  luaL_getmetatable(L, "toolbox.bytes");
  lua_setmetatable(L, -2);

  return 1;
}

static int newbytessized(lua_State *L, size_t size) {
  Bytes *b = (Bytes *)lua_newuserdata(L, sizeof(Bytes) + size * sizeof(char));
  b->size = size;
  b->data = (char *)(b + 1);

  luaL_getmetatable(L, "toolbox.bytes");
  lua_setmetatable(L, -2);

  return 1;
}

static int newbytesstring(lua_State *L, const char *s, size_t l) {
  Bytes *b = (Bytes *)lua_newuserdata(L, sizeof(Bytes) + l * sizeof(char));
  b->size = l;
  b->data = (char *)(b + 1);

  memcpy((void *)b->data, (void *)s, sizeof(char) * l);

  luaL_getmetatable(L, "toolbox.bytes");
  lua_setmetatable(L, -2);

  return 1;
}

static int newbytes(lua_State *L) {
  if (lua_gettop(L) == 0) {
    return newbytesempty(L);
  }

  if (lua_isinteger(L, 1)) {
    return newbytessized(L, luaL_checkinteger(L, 1));
  }

  if (lua_isstring(L, 1)) {
    size_t l;
    const char *s = luaL_checklstring(L, 1, &l);
    return newbytesstring(L, s, l);
  }

  luaL_argerror(L, 1, "expected `string` or `number`");
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
