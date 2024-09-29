#include "Heap.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#ifndef PUZZLE_H
#define PUZZLE_H

using namespace std;

class Puzzle{
public:
    State *init; // estado inicial
    State *goal; // estado final
    Heap *open; // repositorio de estados por visitar
    Heap *all; // repositorio de de todos los estados que fueron ya generados (esto puede crecer mucho)

    Puzzle();
    Puzzle(string filename);
    Puzzle(State *init, State *goal);
    ~Puzzle();
    void solve(); // opera el algoritmo A*
};
#endif
