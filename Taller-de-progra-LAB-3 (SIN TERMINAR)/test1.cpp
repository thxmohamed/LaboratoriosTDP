#include <iostream>
#include "Simplex.h"

using namespace std;

int main() {
    Simplex s("mochila1.txt");
    cout << "Matriz del problema original:" << endl;
    s.printProblemMatrix();
    s.insertConstraint(5, 2,1); // insertamos variable x2 con restricion  x2 <= 5

    cout << "Matriz del problema con restriccion:" << endl;
    s.printProblemMatrix();

    cout << endl;
}