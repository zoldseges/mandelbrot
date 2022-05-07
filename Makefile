CC := gcc
FLAGS := -Wall -Wextra -pedantic -g
PKGS := glfw3 glew opengl gmp
LIBS := $(shell pkg-config --libs --cflags $(PKGS))

OBJS := $(patsubst build/%.c,build/%.o,$(wildcard src/*.c))
HEADER_RULES := $(patsubst src/%.c,build/%.d,$(wildcard src/*.c))

all: mandelbrot

include $(HEADER_RULES)

build/%.d: src/%.c
	$(CC) -MM -MT $(patsubst build/%.d,build/%.o,$@) $< > $@

build/%.o: src/%.c
	$(CC) -c -o $@ $< $(LIBS) $(FLAGS)

mandelbrot: $(OBJS)
	$(CC) -o $@ $^ $(LIBS) $(FLAGS)

.PHONY:
clean:
	rm build/*
	rm mandelbrot

test: test/bin/complex

test/bin/complex: test/test_complex.c src/compute.c src/compute.h
	$(CC) -o $@ $< $(LIBS) $(FLAGS)
