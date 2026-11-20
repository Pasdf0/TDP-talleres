all: main

State.o: State.cpp State.h
	g++ -g -c State.cpp

Nodo.o: Nodo.cpp Nodo.h 
	g++ -g -c Nodo.cpp

List.o: List.cpp List.h
	g++ -g -c List.cpp

Puzzle.o: Puzzle.cpp Puzzle.h
	g++ -g -c Puzzle.cpp

HashTable.o: HashTable.cpp HashTable.h
	g++ -g -c HashTable.cpp

Heap.o: Heap.cpp Heap.h
	g++ -g -c Heap.cpp

testState: testState.cpp State.o
	g++ -g -ggdb State.o testState.cpp -o testState

testNodo: testNodo.cpp Nodo.o State.o
	g++ -g Nodo.o State.o testNodo.cpp -o testNodo

testList: testList.cpp List.o Nodo.o State.o
	g++ -g List.o Nodo.o State.o testList.cpp -o testList

testHashTable: testHashTable.cpp List.o Nodo.o State.o HashTable.o
	g++ -g HashTable.o List.o Nodo.o State.o testHashTable.cpp -o testHashTable

testHeap: testHeap.cpp Heap.o State.o
	g++ -g Heap.o State.o testHeap.cpp -o testHeap

testPuzzle: testPuzzle.cpp State.o Nodo.o List.o Puzzle.o HashTable.o Heap.o
	g++ -g State.o Nodo.o List.o HashTable.o Heap.o Puzzle.o testPuzzle.cpp -o testPuzzle
	
main: State.o Nodo.o List.o Puzzle.o HashTable.o Heap.o main.cpp
	g++ -g State.o Nodo.o List.o HashTable.o Heap.o Puzzle.o main.cpp -o main

clean:
	rm -f *.o testState testPuzzle testNodo testList testHashTable testHeap main
