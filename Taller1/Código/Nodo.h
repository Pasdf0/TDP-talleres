#include <iostream>
#include "State.h"

class Nodo {
    public:
        State *state;
        Nodo *sig;

        Nodo();
        Nodo(State *state);
        ~Nodo();
};