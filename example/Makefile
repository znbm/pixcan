CC = cc
CCFLAGS = -std=c89 -O1 `sdl-config --cflags`
TARGET = example

all: example.c ../pixcan.h
	$(CC) $(CCFLAGS) -o $(TARGET) $(TARGET).c -lSDL2 -lm
