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

graph: main.o algo.o edges.o nodes.o
	gcc main.o algo.o edges.o nodes.o -o graph

all: graph
clean:
	rm -f *.o
	rm -f main
.PHONEY: all clean

test-memory-1: clean all
	valgrind ./graph < input1.txt

test-memory-2: clean all
	valgrind ./graph < input2.txt