FLAGS = -g -O2

all: main testGraph

Graph.o: Graph.cpp Graph.h
	g++ $(FLAGS) -c Graph.cpp

testGraph: testGraph.cpp Graph.o
	g++ $(FLAGS) testGraph.cpp Graph.o -o testGraph

testMain: testMain.cpp Graph.o
	g++ $(FLAGS) testMain.cpp Graph.o -o testMain

main: main.cpp Graph.o
	g++ $(FLAGS) main.cpp Graph.o -o main

clear: 
	rm -f *.o main testGraph testMain