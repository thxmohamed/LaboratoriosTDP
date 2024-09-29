all: State.o Puzzle.o Heap.o testState testPuzzle testHeap main 

State.o: State.cpp State.h
	g++ -g -c State.cpp

Heap.o: Heap.cpp Heap.h
	g++ -g -c Heap.cpp

Puzzle.o: Puzzle.cpp Puzzle.h
	g++ -g -c Puzzle.cpp

testState: testState.cpp State.o
	g++ -g State.o testState.cpp -o testState

testPuzzle: testPuzzle.cpp Puzzle.o State.o Heap.o
	g++ -g State.o Puzzle.o Heap.o testPuzzle.cpp -o testPuzzle

testHeap: testHeap.cpp Heap.o State.o
	g++ -g State.o Heap.o testHeap.cpp -o testHeap

main: Puzzle.o State.o Heap.o main.cpp
	g++ -g State.o Heap.o Puzzle.o main.cpp -o main

clean:
	rm -f *.o testState testHeap testPuzzle main
