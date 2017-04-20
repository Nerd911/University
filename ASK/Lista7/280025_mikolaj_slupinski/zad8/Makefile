CC = gcc
CFLAGS = -g
OBJECTS = zad8.o approx_sqrt.o

zad8 : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o zad8

%.o : %.c
	$(CC) -c $<

clean:
	@rm -vf *.o
	@rm -vf zad8
