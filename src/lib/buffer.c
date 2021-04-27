#include <lualib.h>
#include <lauxlib.h>
#include <string.h>
#include "buffer.h"
#include "bytes.h"

static int newempty(lua_State *L) {
  Buffer *b = (Buffer *)lua_newuserdata(L, sizeof(Buffer));

  b->size = 0;
  b->data = NULL;

  luaL_getmetatable(L, BUFFER_M_NAME);
  lua_setmetatable(L, -2);

  return 1;
}

static int newfrombytes(lua_State *L) {
  Bytes *b = checkbytes(L, 1);

  Buffer *buf = (Buffer *)lua_newuserdata(L, sizeof(Buffer) + b->size * sizeof(char));

  buf->size = b->size;
  if (buf->size == 0) {
    buf->data = NULL;
  } else {
    buf->data = (char *)(b + 1);
    memcpy((void *)buf->data, (void *)b->data, sizeof(char) * buf->size);
  }

  luaL_getmetatable(L, BUFFER_M_NAME);
  lua_setmetatable(L, -2);

  return 1;
}

static int new(lua_State *L) {
  if (lua_gettop(L) == 0) {
    return newempty(L);
  }

  return newfrombytes(L);
}

static int __len(lua_State *L) {
  Buffer *b = checkbuffer(L, 1);
  lua_pushinteger(L, b->size);
  return 1;
}

static int __tostring(lua_State *L) {
  Buffer *b = checkbuffer(L, 1);
  lua_pushfstring(L, "%s[%d]", BUFFER_M_NAME, b->size);
  return 1;
}

static int bytes(lua_State *L) {
  Buffer *buf = checkbuffer(L, 1);

  Bytes *b = (Bytes *)lua_newuserdata(L, sizeof(Bytes) + buf->size * sizeof(char));
  b->size = buf->size;
  b->data = (char *)(b + 1);

  memcpy((void *)b->data, (void *)buf->data, sizeof(char) * buf->size);

  luaL_getmetatable(L, BYTES_M_NAME);
  lua_setmetatable(L, -2);

  return 1;
}

static const struct luaL_Reg bufferlib_f[] = {
  {"new", new},
  {NULL, NULL}
};

static const struct luaL_Reg bufferlib_m[] = {
  {"__len", __len},
  {"__tostring", __tostring},
  {"bytes", bytes},
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
