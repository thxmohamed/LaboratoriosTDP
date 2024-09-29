#include <iostream>
#include "State.h"
#ifndef HEAP_H
#define HEAP_H

class Heap {
public:
    State **arrState; // arreglo de punteros a estados
    int capacity; // capacidad maxima del arreglo
    int size; // indice del ultimo no ocupado o cantidad de elementos en el arreglo

    Heap(int capacity);
    ~Heap();
    void push(State *state);
    State *pop();
    void swap(int i, int j);
    bool contains(State *state);
    bool isEmpty();
    void heapify(int i);
};
#endif