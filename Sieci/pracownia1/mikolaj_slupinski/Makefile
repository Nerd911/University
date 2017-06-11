#Mikołaj Słupiński (280025)
BIN = traceroute
OBJ = main.o receiver.o utils.o sender.o

traceroute: $(OBJ)
	gcc -std=gnu99 -o traceroute $(OBJ)
	make clean
receiver.o: receiver.c
	gcc -std=gnu99 -c -Wall -Wextra receiver.c

main.o: main.c
	gcc -std=gnu99 -c -Wall -Wextra main.c

utils.o: utils.c
	gcc -std=gnu99 -c -Wall -Wextra utils.c

sender.o: sender.c
	gcc -std=gnu99 -c -Wall -Wextra sender.c

clean:
	@rm -vf *.o
