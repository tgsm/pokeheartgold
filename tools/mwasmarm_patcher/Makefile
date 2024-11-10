.PHONY: all clean

CC := gcc-13
CFLAGS := -O3

.PHONY: all clean

all: mwasmarm_patcher
	@:

clean: ; $(RM) mwasmarm_patcher$(EXE)

mwasmarm_patcher: mwasmarm_patcher.c
	$(CC) $(CFLAGS) -o $@ $<
