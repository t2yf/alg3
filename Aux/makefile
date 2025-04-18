CFLAGS = -Wall -Wextra -g -std=c99
CC = gcc

# gera o executável
myrb: main.o rb_tree.o
	$(CC) -o myrb main.o rb_tree.o

# compila rb_tree.c
rb_tree.o: rb_tree.c rb_tree.h
	$(CC) -c $(CFLAGS) rb_tree.c

# compila main
main.o: main.c rb_tree.h
	$(CC) -c $(CFLAGS) main.c

clean:
	rm -f *.o *~ myrb