#include <string.h>
#include <stdio.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#define FALSE 0
#define TRUE  1

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

  memset(b->data, 0, sizeof(char) * b->size);

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

  luaL_Buffer buffer;

  // Number of characters to write
  size_t size = sizeof(char) * (2 + (b->size > 1 ? 3 * b->size - 1 : 0));

  luaL_buffinitsize(L, &buffer, size);
  luaL_addchar(&buffer, '[');

  char *addr = luaL_prepbuffsize(&buffer, size - 2);

  if (b->size > 0) {
    sprintf(addr, "%02X", b->data[0]);
    addr += 2;
  }

  for (size_t i = 1; i < b->size; i++) {
    sprintf(addr, " %02X", b->data[i]);
    addr += 3;
  }

  luaL_addsize(&buffer, size - 2);
  luaL_addchar(&buffer, ']');

  luaL_pushresult(&buffer);

  return 1;
}

static int eq(lua_State *L) {
  Bytes *x = (Bytes *)luaL_checkudata(L, 1, "toolbox.bytes");
  Bytes *y = (Bytes *)luaL_checkudata(L, 2, "toolbox.bytes");

  if (x->size != y->size) {
    lua_pushboolean(L, FALSE);
    return 1;
  }

  lua_pushboolean(L, memcmp(x->data, y->data, sizeof(char) * x->size) == 0);
  return 1;
}

static const struct luaL_Reg byteslib_f[] = {
  {"new", newbytes},
  {NULL, NULL}
};

static const struct luaL_Reg byteslib_m[] = {
  {"__tostring", tostring},
  {"__len", getsize},
  {"__eq", eq},
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
