#include "Nodo.h"

int main()
{
    Simplex simplex = Simplex();
    simplex.insertObjectiveFunction({1, 1});
    simplex.insertConstraint(4, 1, 1);
    simplex.insertConstraint(2, 1, 1);
    simplex.insertConstraint(3, 1, 1);
    simplex.insertConstraint(5, 1, 1);

    Nodo nodo = Nodo(simplex);
    nodo.printConstraints();
    return 0;
}