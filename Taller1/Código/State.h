#include <iostream>
  
class State {
    public:
      int **board; // tablero size x size
      int size; // tamaño del tablero
      int i0; //fila del cero
      int j0; // columna del cero
      int last_move; // 0 up, 1 down, 2 left, 3 right
      State *parent; // puntero al estado anterior
      int depth;
      int manhattanValue;
      int linearValue;
      int value;
      
      State();
      State(int size, State *parent);
      State(int size, State *parent, int **board);
      bool isSol(); // verifica si es solucion
      ~State();
      void print();
      void print_board();
      State *up();
      State *down();
      State *left();
      State *right();
      State *copy();
      void manhattan();
      void updateManhattan();
      void linear();
      bool equals(State *s);
};