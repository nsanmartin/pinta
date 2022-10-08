CC := gcc
CFLAGS := `sdl2-config --libs --cflags` -ggdb3 -Wall -lm -Werror
BUILD := ./build
HDRS := -I./include
SRCS=./src/*.c

pinta:build
	$(CC) -o $(BUILD)/$@ main.c $(HDRS) $(CFLAGS) $(SRCS)

debug:build
	$(CC) -g -o $(BUILD)/$@ main.c $(HDRS) $(CFLAGS) $(SRCS)

build:
	if [ ! -d build ]; then mkdir build; fi

clean:
	rm $(BUILD)/*

.PHONY: dibu all clean
