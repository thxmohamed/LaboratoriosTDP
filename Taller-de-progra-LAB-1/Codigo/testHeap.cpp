#include "Heap.h"

int main() {
    Heap *h = new Heap(2);
    for(int i=0; i<15; i++) {
        State *s = new State(3);
        s->setBoardValue(0, 0, i);
        h->push(s);
        
    }

    std::cout << "tamaño de la matriz: " << h->size << "\n";
    
   return 0;
   
}