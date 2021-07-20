# Aliasing makefile to ./build/Makefile


# Put it first, so calling `make` is the same as `make main`
main:
	cd build && $(MAKE)

.PHONY: main Makefile

# The catch-all target. Just calls make.
%: Makefile
	cd build && $(MAKE) $@