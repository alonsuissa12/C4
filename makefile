CC = gcc
FLAGS = -Wall -g
nodes.o :nodes.h graph.h nodes.c
	$(CC) $(FLAGS) nodes.c -o nodes.o
edegs.o: edges.h graph.h edges.c
	$(CC) $(FLAGS) -c eddges.c - o eddges.o
algo.o: algo.h nodes.h graph.h
	$(CC) $(FLAGS) -c algo.c -o algo.o
main.o: main.c edges.h nodes.h edges.h algo.h
	$(CC) $(FLAGS) -c main.c -o main.o

main: main.o algo.o edges.o nodes.o
	gcc main.o algo.o edges.o nodes.o -o main

all: main
clean:
	rm -f *.o
	rm -f main
.PHONEY: all clean