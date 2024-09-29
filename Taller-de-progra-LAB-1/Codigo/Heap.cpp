#include "Heap.h"


// Función para construir un Heap con una capacidad
// Se crea un arreglo de estados con la capacidad dada
Heap::Heap(int capacity) {
    this->capacity = capacity;
    this->size = 0;
    this->arrState = new State*[capacity];
}

//Destructor de un heap
Heap::~Heap() {
    delete [] arrState;
}

// Función para intercambiar dos elementos del heap
// Se intercambian los elementos en las posiciones i y j
void Heap::swap(int i, int j) {
    State *temp = arrState[i];
    arrState[i] = arrState[j];
    arrState[j] = temp;
}

// aqui se define si vamos a mantener el heap como min heap o max heap
// en este caso esta realizando un min heap  --> raiz es el menor

// Función para agregar un estado al heap
// Se agrega el estado al final del arreglo y se reordena el arreglo

void Heap::push(State *state) {
    if (size == capacity) {
        std::cout << "Heap is full, capacity" <<  std::endl;

        //se crea un nuevo arreglo con el doble de capacidad
        State **arr_tmp = new State*[capacity*2];
        for(int i=0; i<capacity; i++) {
            arr_tmp[i] = arrState[i];
        }

        //se elimina el arreglo anterior y se asigna el nuevo arreglo
        delete [] arrState;
        arrState = arr_tmp;

        //se actualiza la capacidad del arreglo en el heap
        capacity *= 2;
    }

    //una vez que se tiene espacio en el arreglo se agrega el valor
    //y se ordena el arreglo de acuerdo a las reglas del heap (en este caso min heap)
    arrState[size] = state;
    size++;
    int i = size-1;
    while(i != 0 && arrState[i]->diff < arrState[(i-1)/2]->diff) { // min heap
        swap(i, (i-1)/2);
        i = (i-1)/2;
    }
}


// Función para sacar un estado del heap
// Se saca el estado de la raiz y se reordena el arreglo
State* Heap::pop() {
    if (size == 0) {
        return nullptr;
    }
    State* val = arrState[0]; // retornamos la raiz
    arrState[0] = arrState[size-1]; // ponemos el ultimo elemento en la raiz
    size--;
    heapify(0); // reorganizamos el heap
    
    return val;
}

// Función para reorganizar el heap
// Se reorganiza el heap de acuerdo a las reglas del heap (en este caso min heap)
void Heap::heapify(int i) {
    int left = 2*i+1;
    int right = 2*i+2;
    int min = i;
    if (left < size && arrState[left]->diff < arrState[min]->diff) {
        min = left;
    }
    if (right < size && arrState[right]->diff < arrState[min]->diff) {
        min = right;
    }
    if (min != i) {
        swap(i, min);
        heapify(min);
    }
}

// Función para verificar si un estado esta en el heap
// Se recorre el arreglo de estados y se verifica si el estado esta en el arreglo
bool Heap::contains(State *state) {
    for(int i=0; i<size; i++) {
        if (arrState[i]->equals(state)) {
            return true;
        }
    }
    return false;
}

// Función para verificar si el heap esta vacio
// Se verifica si el tamaño del heap es 0

bool Heap::isEmpty() {
    return size == 0;
}
