#FLAGS = -g
FLAGS = -O2

all: Clique.o testClique main

Clique.o: Clique.cpp Clique.h
	g++ $(FLAGS) -c Clique.cpp

testClique: testClique.cpp Clique.o
	g++ $(FLAGS) testClique.cpp Clique.o -o testClique

main: main.cpp Clique.o
	g++ $(FLAGS) main.cpp Clique.o -o main

clean:
	rm -f *.o testClique main