
CC = gcc
CFLAGS = -Wall -Wextra -mwindows

all: 2048

2048: main.c 2048.c 2048.h
	$(CC) $(CFLAGS) -o 2048 main.c 2048.c

clean:
	rm -f 2048