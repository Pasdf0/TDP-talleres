FLAGS = -g -O2

all: main testSimplex testBranchAndBound

Simplex.o: Simplex.cpp Simplex.h
	g++ $(FLAGS) -c Simplex.cpp

BranchAndBound.o: BranchAndBound.cpp BranchAndBound.h
	g++ $(FLAGS) -c BranchAndBound.cpp

testSimplex: testSimplex.cpp Simplex.o
	g++ $(FLAGS) testSimplex.cpp Simplex.o -o testSimplex

testBranchAndBound: testBranchAndBound.cpp BranchAndBound.o
	g++ $(FLAGS) testBranchAndBound.cpp BranchAndBound.o Simplex.o -o testBranchAndBound

main: main.cpp Simplex.o BranchAndBound.o
	g++ $(FLAGS) main.cpp Simplex.o BranchAndBound.o -o main

clean:
	rm -f *.o main testSimplex testBranchAndBound