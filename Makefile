.PHONY: all test clean build
all: build

CC = gcc

test: test/test.c
	${CC} test/test.c src/hl.c lib/strmap.c -o build/hlib
	./build/hlib

build: test/test.c
	${CC} test/test.c src/hl.c lib/strmap.c -o build/hlib

clean:
	rm -rfv build/*
