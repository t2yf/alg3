CFLAGS = -Wall -Wextra -g -std=c99
CC = gcc

# gera o executável
myht: main.o hash_table.o
	$(CC) -o myht main.o hash_table.o -lm

# compila hash_table.c
hash_table.o: hash_table.c hash_table.h
	$(CC) -c $(CFLAGS) hash_table.c

# compila main
main.o: main.c hash_table.h
	$(CC) -c $(CFLAGS) main.c

clean:
	rm -f *.o *~ myht