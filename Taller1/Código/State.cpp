#include "State.h"

State::State(){
    board=nullptr;
    size = 0;
    parent = nullptr;
    depth = 0;
}

State::State(int size, State *parent) {
    this->size = size;
    this->board = new int*[size];
    for(int i=0; i<size; i++) {
        this->board[i] = new int[size];
        for(int j=0; j<size; j++) {
            this->board[i][j] = 0;
        }
    }
    this->parent = nullptr;
    this->depth = parent->depth + 1;
}

State::State(int size, State *parent, int **board) {
    this->size = size;
    this->board = new int*[size];
    for(int i=0; i<size; i++) {
        this->board[i] = new int[size];
        for(int j=0; j<size; j++) {
            this->board[i][j] = board[i][j];
        }
    }
    this->parent = parent;
    this->depth = 0;
}

State::~State() {
    for(int i=0; i<size; i++) {
        delete [] board[i];
        board[i] = nullptr;
    }
    delete [] board;
    board = nullptr;
}

void State::print_board() {
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void State::print() {
    print_board();
    std::cout << std::endl;
}

bool State::isSol() {
    int  k=1; 
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            if (this->board[i][j] != (k % (size*size))) {
                return false;
            }
            k++;
        }
    }
    return true; 
}

State* State::copy() {
   State *new_state = new State(size, this);
   new_state->board = new int*[size];
    for(int i=0; i<size; i++) {
        new_state->board[i] = new int[size];
        for(int j=0; j<size; j++) {
            new_state->board[i][j] = board[i][j];
        }
    }
    new_state->i0 = i0;
    new_state->j0 = j0;
    new_state->manhattanValue = manhattanValue;
    return new_state;
}

State * State::up() {
    State *new_state = copy();
    new_state->board[i0][j0]=board[i0-1][j0];
    new_state->board[i0-1][j0]=0;
    new_state->i0--;
    new_state->last_move = 0;
    new_state->parent = this;
    new_state->depth = this->depth + 1;
    new_state->updateManhattan();
    new_state->linear();
    return new_state;
}

State * State::down() {
    State *new_state = copy();
    new_state->board[i0][j0]=board[i0+1][j0];
    new_state->board[i0+1][j0]=0;
    new_state->i0++;
    new_state->last_move = 1;
    new_state->parent = this;
    new_state->depth = this->depth + 1;
    new_state->updateManhattan();
    new_state->linear();
    return new_state;
}

State * State::left() {
    State *new_state = copy();
    new_state->board[i0][j0]=board[i0][j0-1];
    new_state->board[i0][j0-1]=0;
    new_state->j0--;
    new_state->last_move = 2;
    new_state->parent = this;
    new_state->depth = this->depth + 1;
    new_state->updateManhattan();
    new_state->linear();
    return new_state;
}

State * State::right() {
    State *new_state = copy();
    new_state->board[i0][j0]=board[i0][j0+1];
    new_state->board[i0][j0+1]=0;
    new_state->j0++;
    new_state->last_move = 3;
    new_state->parent = this;
    new_state->depth = this->depth + 1;
    new_state->updateManhattan();
    new_state->linear();
    return new_state;
}

void State::manhattan() {
    manhattanValue = 0;
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            if (board[i][j] != 0) {
                int i2 = (board[i][j] - 1) / size;
                int j2 = (board[i][j] - 1) % size;
                manhattanValue += abs(i-i2) + abs(j-j2);
            }
        }
    }
}

void State::updateManhattan() {
    if(parent != nullptr) {
        int i2 = (board[parent->i0][parent->j0] - 1) / size;
        int j2 = (board[parent->i0][parent->j0] - 1) % size;
        manhattanValue += abs(parent->i0 - i2) + abs(parent->j0 - j2) - abs(i0 - i2) - abs(j0 - j2);
    }
    else {
        this->manhattan();
    }
}

void State::linear() {
    linearValue = 0;
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            if (board[i][j] != 0) {
                int i2 = (board[i][j] - 1) / size;
                int j2 = (board[i][j] - 1) % size;
                if (i == i2) {
                    for(int k=j+1; k<size; k++) {
                        if (board[i][k] != 0) {
                            int i3 = (board[i][k] - 1) / size;
                            int j3 = (board[i][k] - 1) % size;
                            if (i3 == i && j3 < j2) {
                                linearValue += 2;
                            }
                        }
                    }
                }
                if (j == j2) {
                    for(int k=i+1; k<size; k++) {
                        if (board[k][j] != 0) {
                            int i3 = (board[k][j] - 1) / size;
                            int j3 = (board[k][j] - 1) % size;
                            if (j3 == j && i3 < i2) {
                                linearValue += 2;
                            }
                        }
                    }
                }
            }
        }
    }
}

bool State::equals(State *s) {
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            if (this->board[i][j] != s->board[i][j]) {
                return false;
            }
        }
    }
    return true;
}