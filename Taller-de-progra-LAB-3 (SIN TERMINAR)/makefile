FLAGS = -g

all:  test1

Nodo.o: Nodo.cpp Nodo.h
	g++ $(FLAGS) -c Nodo.cpp

Simplex.o: Simplex.cpp Simplex.h
	g++ $(FLAGS) -c Simplex.cpp

BranchBound.o: BranchBound.cpp BranchBound.h
	g++ $(FLAGS) -c BranchBound.cpp

testNodo: Nodo.o testNodo.cpp
	g++ $(FLAGS) Nodo.o testNodo.cpp -o testNodo

test1: test1.cpp Simplex.o
	g++ $(FLAGS) test1.cpp Simplex.o -o test1

clean:
	rm -f *.o test1 testNodo