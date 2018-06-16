CC = gcc
CFLAGS = -std=gnu99 -pthread

all: program1 program2

program1: phil.c
	$(CC) $(CFLAGS) phil.c -o phil -lrt

program2: phil.c
	$(CC) $(CFLAGS) phil_child.c -o phil_child -lrt

clean:
	rm *.o phil phil_child
