CC = gcc
CFLAGS = -g
OBJECTS = zad9.o

zad9 : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o zad9

%.o : %.c
	$(CC) -c $<

clean:
	@rm -vf *.o
	@rm -vf zad9
