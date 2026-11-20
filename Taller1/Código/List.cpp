#include "List.h"

List::List() {
    head = nullptr;
    tail = nullptr;
    n = 0;
}

void List::add(State *state) {
    Nodo * newNodo = new Nodo(state);
    if (head == nullptr) {
        head = newNodo;
        tail = newNodo;
    } else {
        tail->sig = newNodo;
        tail = newNodo;
    }
    n++;
}

bool List::find(State *state) {
    Nodo * newNodo = new Nodo(state);
    Nodo * current = head;
    while (current != nullptr) {
        if (current->state->equals(state) && (state->depth > current->state->depth)) {
            return true;
        }
        current = current->sig;
    }
    return false;
}

State *List::pop() {
    if (head == nullptr) {
        return nullptr;
    }
    Nodo *current = head;
    head = head->sig;
    if(head == nullptr) {
        tail = nullptr;
    }
    n--;
    return current->state;
}

void List::push(State *state) {
    Nodo *newNodo = new Nodo(state);
    newNodo->sig = head;
    head = newNodo;
    n++;
}

void List::print() {
    Nodo *current = head;
    while (current != nullptr) {
        current->state->print();
        current = current->sig;
    }
}

void List::clear() {
    Nodo *current = head;
    while (current != nullptr) {
        Nodo *next = current->sig;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
    n = 0;
}

List::~List() {
    Nodo *current = head;
    std::cout << "Check2" << std::endl;
    while (current != nullptr) {
        Nodo *next = current->sig;
        delete current;
        current = next;
    }
    head = nullptr;
}