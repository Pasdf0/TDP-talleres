#include "Puzzle.h"

int main() {
    Puzzle *p = new Puzzle();
    p->board = new int*[2];
    p->size = 3;

    for(int i=0; i<3; i++) {
        p->board[i] = new int[3];
    }

    p->board[0][0] = 4;
    p->board[0][1] = 1;
    p->board[0][2] = 8;
    p->board[1][0] = 6;
    p->board[1][1] = 2;
    p->board[1][2] = 7;
    p->board[2][0] = 5;
    p->board[2][1] = 3;
    p->board[2][2] = 0;


    p->solve();
    
    return 0;
}