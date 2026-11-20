#include "Heap.h"

Heap::Heap() {
    this->capacity = 2000;
    this->size = 0;
    this->arr = new State*[this->capacity];
}

Heap::~Heap() {
    delete [] arr;
}

int Heap::getHeuristic(State* state) {
    if (state->size == 2) {
        return state->depth;
    }
    if (state->size == 3) {
        int penalization = 0;
        if (state->depth <= 10) {
            penalization = -3;
        } else if (state->depth <= 20) {
            penalization = -2;
        } else if (state->depth <= 30) {
            penalization = -1;
        } else {
            penalization = 30;
        }
        return state->manhattanValue + state->linearValue + penalization;
    }
    else if (state->size == 4){
        int penalization = 0;
        if (state->depth <= 30) {
            penalization = -9;
        } else if (state->depth <= 50) {
            penalization = -6;
        } else if (state->depth <= 80) {
            penalization = -3;
        } else if (state->depth <= 120) {
            penalization = 8;
        } else {
            penalization = 12;
        }
        return state->manhattanValue + state->linearValue + penalization;
    }
    else {
        int penalization = 0;
        if (state->depth <= 60) {
            penalization = -6;
        } else if (state->depth <= 90) {
            penalization = -3;
        } else if (state->depth <= 100) {
            penalization = 0;
        } else if (state->depth <= 150) {
            penalization = 8;
        } else if (state->depth <= 180) {
            penalization = 12;
        } else {
            penalization = 14;
        }
        return state->manhattanValue + state->linearValue + penalization;
    }
}

void Heap::push(State* state) {
    state->value = getHeuristic(state);
    if (this->size == this->capacity) {
        State **arr_tmp = new State*[this->capacity *2];
        for(int i = 0; i < this->capacity; i++) {
            arr_tmp[i] = arr[i];
        }
        delete[] arr;
        arr = arr_tmp;
        this->capacity *= 2;
    }
    arr[this->size] = state;
    this->size++;
    int i = this->size-1;
    while(i > 0 && arr[i]->value < arr[(i-1)/2]->value) { // min heap
        State* temp = arr[i]; // realizamos el  swap
        arr[i] = arr[(i-1)/2];
        arr[(i-1)/2] = temp;
        i = (i-1)/2;
    }
}

State* Heap::pop() {
    if (this->size == 0) {
        return NULL;
    }
    State* state = arr[0]; // retornamos la raiz
    arr[0] = arr[this->size-1]; // ponemos el ultimo elemento en la raiz
    this->size--; // disminuimos el tamaño
    int i = 0;
    while(2*i+1 < this->size) {
        int left = 2*i+1;
        int right = 2*i+2;
        int min = left;
        if (right < this->size && arr[right]->value < arr[left]->value) {
            min = right;
        }
        if (arr[i]->value < arr[min]->value) {
            break; // ya esta ordenado
        }
        State* temp = arr[i]; // si no cuple orden entonces hacemos el swap
        arr[i] = arr[min];
        arr[min] = temp;
        i = min;
    }
    return state;
}

void Heap::empty() {
    this->size = 0;
    for(int i=0; i<this->capacity; i++) {
        arr[i] = NULL;
    }
    delete [] arr;
    this->capacity = 100;
    arr = new State*[this->capacity];
}