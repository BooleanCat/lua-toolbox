FROM nickblah/lua:5.4-luarocks-alpine

RUN apk add --no-cache build-base

RUN \
  luarocks install busted \
  && luarocks install luacheck
