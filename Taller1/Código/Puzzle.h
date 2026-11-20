#include <iostream>
#include <string>
#include "Heap.h"
using namespace std;


class Puzzle {
public: 
    int **board;  // la matriz que representa el puzzle original
    int size;
    Heap* open;
    HashTable* all;

    Puzzle();
    Puzzle(string filename); // cargar desde filename el tablero inicial
    ~Puzzle();
    State * generate_init(); // genera el estado inicial desde board
    void solve(); // opera el algoritmo A*
    State * solveP1(State* e_init);
    void saveRoad(State * checkpoint, List * road);
};