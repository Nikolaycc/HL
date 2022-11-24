.PHONY: all test clean build
all: build

CC = gcc

test: test/test.c
	${CC} test/test.c src/hl.c lib/strmap.c lib/hl_utlis.c -o build/hlib
	./build/hlib

build: test/test.c
	${CC} test/test.c src/hl.c lib/strmap.c lib/hl_utlis.c -o build/hlib

debug: test/test.c
	${CC} -g test/test.c src/hl.c lib/strmap.c lib/hl_utlis.c -o build/hlib
	gdb ./build/hlib

clean:
	rm -rfv build/*
