CC = gcc
CFLAGS = -g
OBJECTS = zad4.o fibonacci.o

zad4 : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o zad4

%.o : %.c
	$(CC) -c $<

clean:
	@rm -vf *.o
	@rm -vf zad4
