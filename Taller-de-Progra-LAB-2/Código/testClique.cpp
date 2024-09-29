#include "Clique.h"
#include <fstream>

int main() {

    Clique c(10);

    set<int> *R = new set<int>;
    set<int> *P = new set<int>;
    set<int> *X = new set<int>;
    set<set<int>*> *C = new set<set<int>*>;
    for (int i = 0; i < c.size; i++) {
        P->insert(i);
    }

    c.addEdge(0, 1);
    c.addEdge(0, 2);
    c.addEdge(1, 2);
    c.addEdge(1, 3);
    c.addEdge(2, 3);
    c.addEdge(0, 3);

    c.BronKerbosch(R, P, X, C);
    c.printClique(C);

    delete R;
    delete P;
    delete X;
    for(auto clique : *C){
        delete clique;
    }

    return 0;
    
}