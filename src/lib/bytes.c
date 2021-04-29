#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "bytes.h"

static int newempty(lua_State *L) {
  Bytes *b = (Bytes *)lua_newuserdata(L, sizeof(Bytes));
  b->size = 0;
  b->data = NULL;

  luaL_getmetatable(L, BYTES_M_NAME);
  lua_setmetatable(L, -2);

  return 1;
}

static int newsized(lua_State *L, size_t size) {
  Bytes *b = (Bytes *)lua_newuserdata(L, sizeof(Bytes));
  b->size = size;
  b->data = (char *)malloc(sizeof(char) * size);

  memset(b->data, 0, sizeof(char) * b->size);

  luaL_getmetatable(L, BYTES_M_NAME);
  lua_setmetatable(L, -2);

  return 1;
}

static int newstring(lua_State *L, const char *s, size_t l) {
  Bytes *b = (Bytes *)lua_newuserdata(L, sizeof(Bytes));
  b->size = l;
  b->data = (char *)malloc(sizeof(char) * l);

  memcpy((void *)b->data, (void *)s, sizeof(char) * l);

  luaL_getmetatable(L, BYTES_M_NAME);
  lua_setmetatable(L, -2);

  return 1;
}

static int new(lua_State *L) {
  if (lua_gettop(L) == 0) {
    return newempty(L);
  }

  if (lua_isinteger(L, 1)) {
    return newsized(L, luaL_checkinteger(L, 1));
  }

  if (lua_isstring(L, 1)) {
    size_t l;
    const char *s = luaL_checklstring(L, 1, &l);
    return newstring(L, s, l);
  }

  luaL_argexpected(L, false, 1, "string or integer");
}

static int __len(lua_State *L) {
  Bytes *b = checkbytes(L, 1);
  lua_pushinteger(L, b->size);
  return 1;
}

static int __tostring(lua_State *L) {
  Bytes *b = checkbytes(L, 1);

  if (b->size == 0) {
    lua_pushstring(L, "[]");
    return 1;
  }

  luaL_Buffer buffer;

  // Number of characters to write
  size_t size = sizeof(char) * (2 + 3 * b->size - 1);

  luaL_buffinitsize(L, &buffer, size);
  luaL_addchar(&buffer, '[');

  char *addr = luaL_prepbuffsize(&buffer, size - 1);

  for (size_t i = 0; i < b->size; i++) {
    sprintf(addr, "%02X ", b->data[i]);
    addr += 3;
  }

  luaL_addsize(&buffer, size - 2);
  luaL_addchar(&buffer, ']');

  luaL_pushresult(&buffer);

  return 1;
}

static int __eq(lua_State *L) {
  Bytes *x = checkbytes(L, 1);
  Bytes *y = checkbytes(L, 2);

  if (x->size != y->size) {
    lua_pushboolean(L, false);
    return 1;
  }

  lua_pushboolean(L, memcmp(x->data, y->data, sizeof(char) * x->size) == 0);
  return 1;
}

static int __concat(lua_State *L) {
  Bytes *x = checkbytes(L, 1);
  Bytes *y = checkbytes(L, 2);

  size_t size = x->size + y->size;

  Bytes *b = (Bytes *)lua_newuserdata(L, sizeof(Bytes));
  b->size = size;

  b->data = (char *)malloc(sizeof(char) * size);
  memcpy(
    (void *)b->data,
    (void *)x->data,
    sizeof(char) * x->size
  );
  memcpy(
    (void *)(b->data + x->size),
    (void *)y->data,
    sizeof(char) * y->size
  );

  luaL_getmetatable(L, BYTES_M_NAME);
  lua_setmetatable(L, -2);

  return 1;
}

static int __gc(lua_State *L) {
  Bytes *b = checkbytes(L, 1);
  free((void *)b->data);
  b->data = NULL;
  return 0;
}

static const struct luaL_Reg byteslib_f[] = {
  {"new", new},
  {NULL, NULL}
};

static const struct luaL_Reg byteslib_m[] = {
  {"__tostring", __tostring},
  {"__len", __len},
  {"__eq", __eq},
  {"__concat", __concat},
  {"__gc", __gc},
  {NULL, NULL}
};

int luaopen_toolbox_bytes(lua_State *L) {
  luaL_newmetatable(L, BYTES_M_NAME);

  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");

  luaL_setfuncs(L, byteslib_m, 0);
  luaL_newlib(L, byteslib_f);

  return 1;
}
