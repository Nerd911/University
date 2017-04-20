CC = gcc
CFLAGS = -g
OBJECTS = zad5.o mulf.o

zad5 : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o zad5

%.o : %.c
	$(CC) -c $<

clean:
	@rm -vf *.o
	@rm -vf zad5
