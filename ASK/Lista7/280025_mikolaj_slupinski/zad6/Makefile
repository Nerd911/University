CC = gcc
CFLAGS = -g
OBJECTS = zad6.o

zad6 : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o zad6

%.o : %.c
	$(CC) -c $<

clean:
	@rm -vf *.o
	@rm -vf zad6
