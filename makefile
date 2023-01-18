CC = gcc
FLAGS = -Wall -g
nodes.o : graph.h nodes.c
	$(CC) $(FLAGS) -c nodes.c -o nodes.o
edges.o: graph.h edges.c
	$(CC) $(FLAGS) -c edges.c -o edges.o
algo.o: graph.h algo.c
	$(CC) $(FLAGS) -c algo.c -o algo.o
main.o: main.c graph.h
	$(CC) $(FLAGS) -c main.c -o main.o

main: main.o algo.o edges.o nodes.o
	gcc main.o algo.o edges.o nodes.o -o main

all: main
clean:
	rm -f *.o
	rm -f main
.PHONEY: all clean