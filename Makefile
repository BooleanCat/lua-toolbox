.PHONY: check test build configure-pre-commit-hook

COLOUR_GREEN=\033[0;32m
COLOUR_NONE=\033[0m

build:
	luarocks make

test:
	busted --shuffle-tests spec/

check:
	luacheck ./

configure-pre-commit-hook:
	@echo 'make check' > .git/hooks/pre-commit
	@chmod +rx .git/hooks/pre-commit
	@printf '$(COLOUR_GREEN)OK$(COLOUR_NONE)\n'
