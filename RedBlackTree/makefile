CC = gcc
CFLAGS = -Wall -g

all: myrb

myrb: main.o rb_tree.o
	$(CC) $(CFLAGS) -o myrb main.o rb_tree.o

main.o: main.c rb_tree.h
	$(CC) $(CFLAGS) -c main.c

rb_tree.o: rb_tree.c rb_tree.h
	$(CC) $(CFLAGS) -c rb_tree.c

clean:
	rm -f *.o *.out myrb
