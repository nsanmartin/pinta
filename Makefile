CC := gcc
CFLAGS := `sdl2-config --libs --cflags` -ggdb3 -Wall -lm -Werror
BUILD := ./build
HDRS := -I./include
SRCS=./src/*.c

pinta:
	$(CC) -o $(BUILD)/$@ main.c $(HDRS) $(CFLAGS) $(SRCS)

debug:
	$(CC) -g -o $(BUILD)/$@ main.c $(HDRS) $(CFLAGS) $(SRCS)

all: $(EXEC)

clean:
	rm $(BUILD)/*

.PHONY: dibu all clean
