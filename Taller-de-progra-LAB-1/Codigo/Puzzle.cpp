#include "Puzzle.h"


// Constructor de la clase Puzzle
// Se inicializan los atributos del puzzle
Puzzle::Puzzle() {
    init = new State();
    goal = new State();
    open = new Heap(1000);
    all = new Heap(1000);
}


// Constructor de la clase Puzzle
// Se inicializan los atributos del puzzle con el estado inicial y el estado final
Puzzle::Puzzle(State *init, State *goal) {
    this->init = init;
    this->goal = goal;
    open = new Heap(1000);
    all = new Heap(1000);
}


// Constructor de la clase Puzzle
// Se inicializan los atributos del puzzle con los datos de un archivo
Puzzle::Puzzle(string filename) {
    ifstream file;
    open = new Heap(1000);
    all = new Heap(1000);
    file.open(filename);
    if(!file.is_open()) {
        cout << "No se pudo abrir el archivo\n";
        return;
    }
    string line;
    stringstream ss;
    int size, n = 0;
    if(getline(file, line, '\n')) {
        ss << line;
        while(ss >> size) {
            n++;
        }
    }
    file.close();
    int **board;
    board = new int*[n];
    for(int i = 0; i < n; i++) {
        board[i] = new int[n];
    }
    file.open(filename);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            file >> board[i][j];
        }
    }
    file.close();
    init = new State(n, nullptr, board);
    goal = init->generateGoal();
}

// Destructor de la clase Puzzle
Puzzle::~Puzzle() {
    delete init;
    delete goal;
    delete open;
    delete all;
}

// Función para resolver el puzzle
// Se resuelve el puzzle con el algoritmo A*
// Se agregan los estados al heap de abiertos y se van sacando los estados del heap
// Se generan los hijos de cada estado y se agregan al heap de abiertos
// Se verifica si el estado es igual al estado final
void Puzzle::solve() {
    if(init == nullptr) {
        cout << "No se pudo generar el estado inicial\n";
        return;
    }
    if (init->size == 1){
        cout << "El tablero ya esta resuelto\n";
        return;
    }

    open->push(init); // agrega en los abiertos el tablero inicial
    all->push(init); // agrega en todos (ex cerrados) el tablero inicial
    while(open->size > 0) {
        State *current = open->pop();
        if(current->equals(goal)) {
            cout << "Encontramos la solucion:\n";
            current->print();
            current->contarMovimientos();
            cout << "En la cantidad de pasos: " << current->moves << endl;
            return;
        }
        this->all->push(current);
        State **successors = current->findChildren();
        for(int i = 0; i < 4; i++) {
            if(successors[i] != nullptr) {
                if(!all->contains(successors[i])) {
                    if(!open->contains(successors[i])) {
                        successors[i]->diff = successors[i]->manhattan(goal) + successors[i]->conflict(goal);
                        open->push(successors[i]);
                    } else {
                        delete successors[i];
                    }
                } else {
                    delete successors[i];
                }
            }
        }
    }
    cout << "No se encontro la solucion\n";
    return;
}
