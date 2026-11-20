#include <iostream>
#include "HashTable.h"

class Heap {
    public:
        State** arr;
        int capacity;
        int size;

        Heap();
        ~Heap();
        int getHeuristic(State* state);
        void push(State* val);
        State* pop();
        void empty();
};