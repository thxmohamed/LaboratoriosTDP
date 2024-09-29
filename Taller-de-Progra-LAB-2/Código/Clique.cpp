#include "Clique.h"
#include <iostream>

// Entrada: Matriz de adyacencia del grafo y tamaño del grafo
// Salida: Clase Clique
// Descripción: Constructor de la clase Clique que inicializa el tamaño del grafo,
//              redimensiona la lista de adyacencia y establece el tamaño del clique máximo en 0
Clique::Clique(int size) {
    this->size = size;
    listaAdyacencia.resize(size);
    maxCliqueSize = 0;
}

// Entrada: Vértices u y v
// Salida: Ninguna
// Descripción: Función que agrega una arista entre los vértices u y v en la lista de adyacencia
void Clique::addEdge(int u, int v) {
    listaAdyacencia[u].insert(v);
    listaAdyacencia[v].insert(u);
}

// Entrada: Vértice v
// Salida: Conjunto de vecinos de v
// Descripción: Función que retorna el conjunto de vecinos de un vértice v
const set<int>& Clique::neighbours(int v) const {
    return listaAdyacencia[v];
}

// Entrada: Conjunto de vértices P y X
// Salida: Vértice pivote (int)
// Descripción: Función que elige el vértice de mayor grado de un conjunto de vértices P unión X y lo retorna como pivote
int Clique::elegirPivote(set<int>* P, set<int>* X) {
    set<int> unionPX;
    set_union(P->begin(), P->end(), X->begin(), X->end(), inserter(unionPX, unionPX.begin()));
    int pivote = -1;
    int maxDegree = -1;
    for (int v : unionPX) {
        int degree = listaAdyacencia[v].size();
        if (degree > maxDegree) {
            maxDegree = degree;
            pivote = v;
        }
    }
    return pivote;
}

// Entrada: Conjunto de vértices R, P y X y conjunto de cliques C
// Salida: Conjunto de cliques C (con los cliques máximos de tamaño maxCliqueSize)
// Descripción: Algoritmo de Bron-Kerbosch para encontrar cliques máximos en un grafo, optimizado con pivote y poda de ramas
set<set<int>*>* Clique::BronKerbosch(set<int>* R, set<int>* P, set<int>* X, set<set<int>*>* C) {
    // Caso base: si P y X están vacíos, se ha encontrado un clique máximo
    if (P->empty() && X->empty()) {
        if (R->size() > maxCliqueSize) {
            // Se ha encontrado un nuevo clique máximo de mayor tamaño
            maxCliqueSize = R->size();
            for (auto clique : *C) {
                delete clique;
            }
            C->clear();
            C->insert(new set<int>(*R));
        } else if (R->size() == maxCliqueSize) {
            C->insert(new set<int>(*R));
        }
        return C;
    }

    // Elegir un pivote y calcular la diferencia P \ N(pivot)
    int pivot = elegirPivote(P, X);
    const set<int>& pivotNeighbors = neighbours(pivot);
    set<int> difference;
    set_difference(P->begin(), P->end(), pivotNeighbors.begin(), pivotNeighbors.end(), inserter(difference, difference.begin()));

    // Para cada vértice en la diferencia, extender el clique R
    for (auto v : difference) {
        if (R->size() + P->size() <= maxCliqueSize) {
            break;
        }

        set<int>* R1 = new set<int>(*R);
        R1->insert(v);

        const set<int>& neighbors = neighbours(v);
        set<int>* P1 = new set<int>;
        set_intersection(P->begin(), P->end(), neighbors.begin(), neighbors.end(), inserter(*P1, P1->begin()));

        set<int>* X1 = new set<int>;
        set_intersection(X->begin(), X->end(), neighbors.begin(), neighbors.end(), inserter(*X1, X1->begin()));

        // Llamada recursiva al algoritmo de Bron-Kerbosch
        BronKerbosch(R1, P1, X1, C);

        P->erase(v);
        X->insert(v);

        delete R1;
        delete P1;
        delete X1;
    }
    return C;
}

// Entrada: Conjunto de cliques C
// Salida: Impresión de los cliques máximos de tamaño maxCliqueSize
// Descripción: Función que imprime el primer clique máximo de tamaño maxCliqueSize
void Clique::printClique(set<set<int>*>* C) {
    if (C->empty()) {
        cout << "No hay cliques en el grafo" << endl;
        return;
    }
    cout << "Encontrado el mayor clique máximo de tamaño " << maxCliqueSize << endl;
    for (auto clique : *C) {
        cout << "{ ";
        for (int v : *clique) {
            cout << v << " ";
        }
        cout << "}" << endl;
        break;  // Solo imprimir el primer clique máximo encontrado
    }
}
