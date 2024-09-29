#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <set>


using namespace std;

class Clique {
    public:

    // Atributos de la clase Clique
    vector<set<int>> listaAdyacencia; // Lista de adyacencia del grafo
    int size; // Tamaño del grafo
    int maxCliqueSize = 0; // Tamaño de la clique máxima

    // Métodos de la clase Clique

    Clique(int size); // Constructor de la clase Clique
    void addEdge(int u, int v); // Método que agrega una arista al grafo
    set<set<int>*>* BronKerbosch(set<int> *R, set<int> *P, set<int> *X , set<set<int>*> *C); // Algoritmo de Bron-Kerbosch
    const set<int>& neighbours(int v) const;
    int elegirPivote(set<int>* P, set<int>* X);
    void printClique(set<set<int>*>* C);

};