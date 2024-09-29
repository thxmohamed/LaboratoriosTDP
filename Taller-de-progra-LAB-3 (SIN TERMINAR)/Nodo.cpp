#include "Nodo.h"

Nodo::Nodo()
{
}

Nodo::Nodo(Simplex simplex)
{
    this->simplex = simplex;
}

Nodo::~Nodo()
{
}

void Nodo::addConstraint(float b, int var, int type)
{
    this->simplex.insertConstraint(b, var, type);
}

void Nodo::removeConstraint(int i)
{
    std::vector<std::vector<float>> newConstraints;
    int size = this->simplex.initialA.size();
    for (int j = 0; j < size; j++)
    {
        if (j != i)
        {
            newConstraints.push_back(this->simplex.initialA[j]);
        }
    }
    this->simplex.initialA = newConstraints;
}

void Nodo::printConstraints()
{
    for (std::vector<float> constraint : this->simplex.initialA)
    {
        for (float i : constraint)
        {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
}
