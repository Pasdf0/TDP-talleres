#include <iostream>
#include "Nodo.h"

class List {
    public:
        Nodo * head;
        Nodo * tail;
        int n;

        List();
        void add(State *state);
        bool find(State *state);
        State *pop();
        void push(State* state);
        void print();
        void clear();
        ~List();
};