.PHONY: test build

build:
	luarocks make

test:
	busted spec/*
