#include "BranchAndBound.h"

BranchAndBound::BranchAndBound(Simplex simplex)
{
    Nodo nodo = Nodo(simplex);
    this->nodosActivos.push_back(nodo);
    this->mejorCota = 0;
}

BranchAndBound::~BranchAndBound()
{
}

float BranchAndBound::cotaInf(Nodo nodo)
{
    vector<float> x = nodo.getSimplex().solve();
    float cota = 0;
    for(float i : x)
    {
        cota += floor(i);
    }
    return cota;
}

float BranchAndBound::cotaSup(Nodo nodo)
{
    vector<float> x = nodo.getSimplex().solve();
    float cota = 0;
    for(float i : x)
    {
        cota += i;
    }
    return cota;
}

std::vector<float> BranchAndBound::solve()
{
    while(!this->nodosActivos.empty())
    {
        Nodo nodo = this->nodosActivos.back();
        this->nodosActivos.pop_back();
        if(nodo.getSimplex().isFeasible())
        {
            if(nodo.getSimplex().getZ() > this->mejorCota)
            {
                this->mejorCota = nodo.getSimplex().getZ();
                this->mejorSolucion = nodo.getSimplex().solve();
            }
            if(this->cotaSup(nodo) > this->mejorCota)
            {
                Nodo nodo1 = Nodo(nodo.getSimplex());
                nodo1.addConstraint(0, nodo.getSimplex().getPivotColumn(), 1);
                this->nodosActivos.push_back(nodo1);
                Nodo nodo2 = Nodo(nodo.getSimplex());
                nodo2.addConstraint(1, nodo.getSimplex().getPivotColumn(), 0);
                this->nodosActivos.push_back(nodo2);
            }
        }
    }
    return this->mejorSolucion;
}