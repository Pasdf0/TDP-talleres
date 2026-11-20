#include <iostream>
#include "Nodo.h"

int main() {
    Nodo *n1 = new Nodo();
    Nodo *n2 = new Nodo();
    int** board1;
    int** board2;

    board1[0][0] = 4;
    board1[0][1] = 1;
    board1[0][2] = 8;
    board1[1][0] = 6;
    board1[1][1] = 2;
    board1[1][2] = 7;
    board1[2][0] = 5;
    board1[2][1] = 3;
    board1[2][2] = 0;

    board2[0][0] = 4;
    board2[0][1] = 1;
    board2[0][2] = 8;
    board2[1][0] = 6;
    board2[1][1] = 2;
    board2[1][2] = 7;
    board2[2][0] = 5;
    board2[2][1] = 0;
    board2[2][2] = 3;

    n1->state = new State(3, nullptr, board1);
    n2->state = new State(3, nullptr, board2);
    
    n1->sig = n2;
    n1->sig->state->print();
    return 0;
}