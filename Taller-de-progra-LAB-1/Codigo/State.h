#include <iostream>
#ifndef STATE_H
#define STATE_H
  
/// vamos a definir la clase State de manera abstracta
class State {
    public:
      int **board; // tablero size x size
      int size;
      // al cargar el archivo busco donde esta el 0
      int i0; //fila del cero
      int j0; // columna del cero
      State *parent;
      int moves; // cantidad de movimientos realizados hasta llegar a este estado
      int diff; // diferencia entre el estado actual y el final
      //se calcula en base a la distancia de manhattan entre ambos estados


      State();
      State(int size);
      State(int size, State *parent);
      State(int size, State *parent, int **board);
      State(int size, State *parent, int **board, State *goal);

      void buscarCero();
      void setBoardValue(int i, int j, int value);
      void initBoard();

      void contarMovimientos();

      bool isSol(); // verifica si es solucion
      ~State();

      int diffManhattan(int x1, int y1, int x2, int y2); // calcula la distancia de manhattan entre dos puntos
      int manhattan(State *goal); // calcula la distancia de manhattan entre dos estados
      int conflict(State *goal); // calcula la cantidad de conflictos entre dos estados
      
      void print(); // print recursively
      void print_board();
      State *generateGoal(); // genera el estado final
      State *up();
      State *down();
      State *left();
      State *right();
      State *copy();
      bool equals(State *s); // compara dos estados
      State **findChildren(); // expande el estado actual
      //bool equals(State *s); // compara dos estados

};
#endif