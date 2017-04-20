CC = gcc
CFLAGS = -g -nostdlib
OBJECTS = zad7.o

zad7 : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o zad7

%.o : %.c
	$(CC) -c $<

clean:
	@rm -vf *.o
	@rm -vf zad7
