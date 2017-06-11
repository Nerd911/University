CC = gcc
CFLAGS = -g
OBJECTS = zad3.o insert_sort.o

zad3 : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o zad3

%.o : %.c
	$(CC) -c $<

clean:
	@rm -vf *.o
	@rm -vf zad3
