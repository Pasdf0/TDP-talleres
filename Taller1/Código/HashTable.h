#include <iostream>
#include "List.h"

class HashTable {
    public:
        List **array;
        int sizeH;

        HashTable();
        HashTable(int size);
        void add(State *state);
        bool find(State *state);
        int hash(State *state);
        void clear();
        void checkColission();
        ~HashTable();
};