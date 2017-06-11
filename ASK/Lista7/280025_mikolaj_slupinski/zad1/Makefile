CC = gcc
CFLAGS = -g
OBJECTS = zad1.o clz.o

zad1 : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o zad1

%.o : %.c
	$(CC) -c $<

clean:
	@rm -vf *.o
	@rm -vf zad1
