.PHONY: test build

build:
	luarocks make

test:
	busted --shuffle-tests spec/*
