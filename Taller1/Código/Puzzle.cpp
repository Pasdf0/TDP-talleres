#include "Puzzle.h"
#include <fstream>
#include <sstream>

using namespace std;


Puzzle::Puzzle() {
    this->size=0;
    this->board=nullptr;
    this->open = nullptr;
    this->all = nullptr;
}

Puzzle::Puzzle(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout<<"No se pudo abrir el archivo"<<endl;
        return;
    }
    string line;
    stringstream ss;
    int num, n=0;
    if(getline(file,line,'\n')){
        ss << line;
        while(ss >> num) {
            n++;
        }
    }
    file.close();

    int **board;
    board = new int*[n];
    for (int i = 0; i < n; i++) {
        board[i] = new int[n];
    }
    file.open(filename);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file >> board[i][j];
        }
    } 
    file.close();
    this->board = board;
    this->size = n;
}

State * Puzzle::generate_init() {
    // asumiendo que board ya esta cargado
    State *e = new State(this->size, nullptr, this->board);
    e->parent=nullptr;
    e->last_move=-1;
    e->i0=-1; // caso de no encontrar el cero
    e->j0=-1;
    if (this->board==nullptr) {
        cout << "No se ha cargado el tablero" << endl;
        return nullptr;
    }
    e->manhattan();
    e->linear();
    all = new HashTable(this->size); // tabla de hash
    open = new Heap(); // cola de prioridad
    // buscar el cero
    for (int i=0; i<this->size; i++) {
        for (int j=0; j<this->size; j++) {
            if (board[i][j]==0) {
                e->i0=i;
                e->j0=j;
                return e;
            }
        }
    }
    return nullptr;
}

void Puzzle::solve() {
    State *e_init= generate_init(); // genera el estado inicial
    if (e_init==nullptr) {
        cout << "No se pudo generar el estado inicial" << endl;
        return;
    }
    List * solution = new List();
    State * checkpoint = e_init;
    //cout << "El problema es el final" << endl;
    checkpoint = solveP1(e_init);
    //checkpoint->print();
    //cout << "Checkpoint depth: " << checkpoint->depth << "  Solution n: " << solution->n << endl;
    if (checkpoint == nullptr) {
        cout<< "No se encontro solucion" << endl;
    }
    saveRoad(checkpoint, solution);
    solution->print();
    cout << solution->n-1 << " Pasos" << endl;
    //checkpoint->print();
}

State * Puzzle::solveP1(State *e_init) {
    open->push(e_init); // agrega en los abierto el tablero inicial
    all->add(e_init); // agrega en todos (ex cerrados )el tablero inicial
    while (open->size!=0) { // mientras existan nodos por visitar
        State *e = open->pop(); // deberia obtener el mejor estado
        if (e->isSol()) {
            return e;
        }

        if (e->i0!=0 && e->last_move!=1) { // si no esta en la primera fila entonces puedo subir el 0
            State *e_up = e->up();
            if (!all->find(e_up)) {
                open->push(e_up);
                all->add(e_up);
            }
        }

        if (e->i0!=size-1 && e->last_move!=0) { // si no esta en la ultima fila entonces puedo bajar el 0
            State *e_down = e->down();
            if (!all->find(e_down)) {
                open->push(e_down);
                all->add(e_down);
            }
        }

        if (e->j0!=0 && e->last_move!=3) { // si no esta en la primera columna entonces puedo mover a la izquierda
            State *e_left = e->left();
            if (!all->find(e_left)) {
                open->push(e_left);
                all->add(e_left);
            }
        }

        if (e->j0!=size-1 && e->last_move!=2) { // si no esta en la ultima columna entonces puedo mover a la derecha
            State *e_right = e->right();
            if (!all->find(e_right)) {
                open->push(e_right);
                all->add(e_right);
            }
        }
    }
    return nullptr;
}

Puzzle::~Puzzle() {
    if (this->board!=nullptr) {
        for (int i=0; i<this->size; i++) {
            delete[] this->board[i];
        }
        delete[] this->board;
    }
    if (this->open!=nullptr) {
        this->open = nullptr;
    }
    if (this->all!=nullptr) {
        delete this->all;
        this->all = nullptr;
    }
}

void Puzzle::saveRoad(State * checkpoint, List * road) {
    State *current = checkpoint;
    while (current != nullptr) {
        road->push(current->copy());
        current = current->parent;
    }
}