#include <iostream>
#include "Heap.h"

int main() {
    int size = 4;
    int **board;
    board = new int*[size];
    for(int i=0; i<size; i++) {
        board[i] = new int[size];
    }
    board[0][0] = 12;
    board[0][1] = 0;
    board[0][2] = 8;
    board[0][3] = 10;
    board[1][0] = 4;
    board[1][1] = 5;
    board[1][2] = 14;
    board[1][3] = 2;
    board[2][0] = 6;
    board[2][1] = 7;
    board[2][2] = 11;
    board[2][3] = 15;
    board[3][0] = 3;
    board[3][1] = 13;
    board[3][2] = 1;
    board[3][3] = 9;

    State* state = new State(size, nullptr, board);
    state->manhattan();
    state->i0 = 0;
    state->j0 = 1;
    Heap* heap = new Heap();
    heap->push(state);
    heap->push(state->down());
    heap->push(state->left());
    heap->push(state->right());
    heap->pop()->print();
    heap->arr[0]->print();
    return 0;
}