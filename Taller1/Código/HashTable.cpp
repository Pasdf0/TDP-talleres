#include "HashTable.h"

using namespace std;

HashTable::HashTable() {
    sizeH = 2000;
    array = new List*[sizeH];
    for (int i = 0; i < sizeH; i++) {
        array[i] = new List();
    }
}

HashTable::HashTable(int sz) {
    sizeH = sz*sz*100;
    array = new List*[sizeH];
    for (int i = 0; i < sizeH; i++) {
        array[i] = new List();
    }
}

void HashTable::add(State *state) {
    int index = hash(state);
    array[index]->add(state);
}

bool HashTable::find(State *state) {
    if (state == nullptr) {
        return false;
    }
    int index = hash(state);
    return array[index]->find(state);
}

int HashTable::hash(State *state) {
    long int hash = 0;
    int primes[25] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    for (int i = 0; i < state->size; i++) {
        for (int j = 0; j < state->size; j++) {
            hash = hash + state->board[i][j] * primes[i * state->size + j];
        }
    }
    hash = 14159 * hash;
    hash = hash % sizeH;
    return hash;
}

void HashTable::clear() {
    for (int i = 0; i < sizeH; i++) {
        delete array[i];
        array[i] = new List();
    }
}

void HashTable::checkColission() {
    int colissions = 0;
    int empty = 0;
    int justOne = 0;
    for (int i = 0; i < sizeH; i++) {
        if (array[i]->n > 1) {
            colissions++;
        }
        else if (array[i]->n == 0) {
            empty++;
        }
        else {
            justOne++;
        }
    }
    std::cout << "Collisions: " << colissions << " Empty: " << empty << " JustOne: " << justOne << std::endl;
}

HashTable::~HashTable() {
    for (int i = 0; i < sizeH; i++) {
        delete array[i];
        array[i] = nullptr;
    }
    array = nullptr;
}