.PHONY: check test build

build:
	luarocks make

test:
	busted --shuffle-tests spec/

check:
	luacheck ./
