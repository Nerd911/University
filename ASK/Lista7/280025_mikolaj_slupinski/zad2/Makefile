CC = gcc
CFLAGS = -g
OBJECTS = zad2.o lcm_gcd.o

zad2 : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o zad2

%.o : %.c
	$(CC) -c $<

clean:
	@rm -vf *.o
	@rm -vf zad2
