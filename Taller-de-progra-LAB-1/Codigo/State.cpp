#include "State.h"
/*
Este archivo esta dedicado a definir los metodos de la clase State

*/

// Constructor de la clase State
// Se inicializan los atributos del estado

State::State(){
    board=nullptr; //NULL
    size=0;
    diff=0;
    moves=0;
    parent=nullptr;
}

// Constructor de la clase State
// Se inicializa el tamaño del tablero
// Se inicializa el tablero con 0 en todas las posiciones

State::State(int size) {
    this->size = size;
    this->board = new int*[size];
    diff = 0;
    moves = 0;
    for(int i=0; i<size; i++) {
        this->board[i] = new int[size];
        for(int j=0; j<size; j++) {
            this->board[i][j] = 0;
        }
    }
    this->parent = nullptr;

}

// Constructor de la clase State
// Se inicializa el tamaño del tablero y el estado padre
// Se inicializa el tablero con 0 en todas las posiciones

State::State(int size, State *parent) {
    this->size = size;
    this->board = new int*[size];
    diff = 0;
    moves = 0;
    for(int i=0; i<size; i++) {
        this->board[i] = new int[size];
        for(int j=0; j<size; j++) {
            this->board[i][j] = 0;
        }
    }
    this->parent = parent;
}

// Constructor de la clase State
// Se inicializa el tamaño del tablero, el tablero, los movimientos y el estado padre
State::State(int size, State *parent, int **board) {
    this->size = size;
    this->board = new int*[size];
    moves = 0;
    for(int i=0; i<size; i++) {
        this->board[i] = new int[size];
        for(int j=0; j<size; j++) {
            this->board[i][j] = board[i][j];
        }
    }
    this->buscarCero();
    this->parent = parent;
}

// Constructor de la clase State
// Se inicializa el tamaño del tablero, el tablero, los movimientos, el estado padre y el estado objetivo

State::State(int size, State *parent, int **board, State *goal){
    this->size = size;
    moves = 0;
    this->board = new int*[size];
    for(int i=0; i<size; i++) {
        this->board[i] = new int[size];
        for(int j=0; j<size; j++) {
            this->board[i][j] = board[i][j];
        }
    }
    this->parent = parent;
}

// Destructor de la clase State

State::~State() {
    int size=0;
    for(int i=0; i<this->size; i++) {
        delete [] board[i];
    }
    delete [] board;
}

// Función que busca la posición del 0 en el tablero

void State::buscarCero() {
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            if (board[i][j] == 0) {
                i0 = i;
                j0 = j;
                return; // se asume que hay solo un cero
            }
        }
    }
}

// Función que asigna un valor a una posición del tablero

void State::setBoardValue(int i, int j, int value) {
    board[i][j] = value;
}

// Función que genera el estado objetivo
// El estado objetivo es un tablero ordenado de menor a mayor

State* State::generateGoal() {
    State *goal = new State(size);
    int k=1;
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            goal->setBoardValue(i, j, k);
            k++;
        }
    }
    goal->setBoardValue(size-1, size-1, 0);
    goal->i0 = size-1;
    goal->j0 = size-1;
    return goal;
}

// Función que imprime el tablero del estado actual

void State::print_board() {
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Función que cuenta los movimientos realizados para alcanzar el estado actual
// Se cuenta recursivamente los movimientos desde el estado actual hasta el estado inicial

void State::contarMovimientos(){
    int movimientos = 0;
    State *aux = this;
    while(aux->parent != nullptr){
        movimientos++;
        aux = aux->parent;
    }
    this->moves = movimientos;
}

// Función que imprime recursivamente el tablero del estado actual
// Si el estado tiene un padre, se imprime el tablero del padre

void State::print() {
    if (parent != nullptr) {
        parent->print();
       
    } 
    
    print_board();
    std::cout << std::endl;
}

// Función que retorna si el estado actual es el estado objetivo
// Un estado es objetivo si el tablero está ordenado de menor a mayor

bool State::isSol() {
   int  k=1; 
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            if (this->board[i][j] != (k%(size*size)))  {
                return false;
            }
            k++;
        }
    }
    return true; 
}

// Función que retorna un nuevo estado copiando el estado actual

State* State::copy() {
   State *new_state = new State(size, this);
   new_state->board = new int*[size];
    for(int i=0; i<size; i++) {
        new_state->board[i] = new int[size];
        for(int j=0; j<size; j++) {
            new_state->board[i][j] = board[i][j];
        }
    }
    new_state->i0 = i0;
    new_state->j0 = j0;
     return new_state;
}

// Función que retorna un nuevo estado a partir de mover el 0 hacia arriba
// Si no se puede mover hacia arriba, se retorna nullptr

State *State::up() {
  if (this->i0!=0) { // si no esta en la primera fila entonces puedo subir el 0
    State *new_state = this->copy();
    new_state->board[i0][j0]=board[i0-1][j0];
    new_state->board[i0-1][j0]=0;
    new_state->i0--;
    return new_state;
  }
  return(nullptr);
}

// Función que retorna un nuevo estado a partir de mover el 0 hacia abajo
// Si no se puede mover hacia abajo, se retorna nullptr

State *State::down() {
  if (i0!=size-1) { // si no esta en la primera fila entonces puedo subir el 0
    State *new_state = this->copy();
    new_state->setBoardValue(i0, j0, board[i0+1][j0]);
    new_state->setBoardValue(i0+1, j0, 0);
    new_state->i0++;
    return new_state;
  }
  return(nullptr);
}

// Función que retorna un nuevo estado a partir de mover el 0 a la derecha
// Si no se puede mover a la derecha, se retorna nullptr

State *State::right() {
  if (j0!=size-1) { // si no esta en la primera fila entonces puedo subir el 0
    State *new_state = this->copy();
    new_state->setBoardValue(i0, j0, board[i0][j0+1]);
    new_state->setBoardValue(i0, j0+1, 0);
    new_state->j0++;
    return new_state;
  }
  return(nullptr);
}

// Función que retorna un nuevo estado a partir de mover el 0 a la izquierda
// Si no se puede mover a la izquierda, se retorna nullptr

State *State::left() {
  if (j0!=0) { // si no esta en la primera fila entonces puedo subir el 0
    State *new_state = this->copy();
    new_state->setBoardValue(i0, j0, board[i0][j0-1]);
    new_state->setBoardValue(i0, j0-1, 0);
    new_state->j0--;
    return new_state;
  }
  return(nullptr);
}

// Función que retorna si dos estados son iguales
// Dos estados son iguales si sus tableros son iguales

bool State::equals(State *s) {
    // comparamos solo el tablero
    for(int i=0; i<this->size; i++) {
        for(int j=0; j<this->size; j++) {
            if (this->board[i][j] != s->board[i][j]) {
                return false;
            }
        }
    }
    // el resto de los elementos (size,parent,i0,j0) de state debiesen ser iguales 
    // sino existe un error en la implementacion
    return true;
}


// Función que retorna la diferencia de manhattan entre dos puntos
// La diferencia de manhattan es la suma de las diferencias absolutas en x y en y

int State::diffManhattan(int x1, int y1, int x2, int y2) {
    return abs(x1-x2) + abs(y1-y2);
}

// Función que retorna la suma de las diferencias de manhattan entre el estado actual y el estado objetivo

int State::manhattan(State *goal) {
    int diff = 0;
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            if (board[i][j] != 0) {
                int x1 = i;
                int y1 = j;
                int x2 = (board[i][j]-1)/size;
                int y2 = (board[i][j]-1)%size;
                diff += diffManhattan(x1, y1, x2, y2);
            }
        }
    }
    return diff;
}


// Función que retorna un arreglo de estados hijos a partir de un estado actual,
// Estos son los estados que se pueden obtener a partir de mover el 0 en el tablero
// Si no se puede mover en alguna dirección, se retorna nullptr
State **State::findChildren() {
    State **states = new State*[4];
    states[0] = this->up();
    states[1] = this->down();
    states[2] = this->left();
    states[3] = this->right();
    return states;
}

// Función que retorna la cantidad de conflictos lineales en el tablero actual
// Un conflicto es cuando dos piezas que deberían estar juntas no lo están
// y están en la misma fila o columna

int State::conflict(State *goal) {
    int conflicts = 0;
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            if (board[i][j] != 0) {
                int x1 = i;
                int y1 = j;
                int x2 = (board[i][j]-1)/size;
                int y2 = (board[i][j]-1)%size;
                if (x1 == x2) {
                    for(int k=0; k<size; k++) {
                        if (board[x1][k] != 0 && board[x2][k] != 0) {
                            int y3 = k;
                            int y4 = (board[x1][k]-1)%size;
                            if (y3 != y4 && y1 == y4 && y2 == y3) {
                                conflicts++;
                            }
                        }
                    }
                }
                if (y1 == y2) {
                    for(int k=0; k<size; k++) {
                        if (board[k][y1] != 0 && board[k][y2] != 0) {
                            int x3 = k;
                            int x4 = (board[k][y1]-1)/size;
                            if (x3 != x4 && x1 == x4 && x2 == x3) {
                                conflicts++;
                            }
                        }
                    }
                }
            }
        }
    }
    return conflicts;
}
