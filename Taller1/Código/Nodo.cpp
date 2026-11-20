#include "Nodo.h"

Nodo::Nodo() {
    state = nullptr;
    sig = nullptr;
}

Nodo::Nodo(State *state) {
    this->state = state;
    this->sig = nullptr;
}

Nodo::~Nodo() {
    delete state;
    state = nullptr;
}