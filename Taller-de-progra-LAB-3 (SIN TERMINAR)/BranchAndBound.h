#include "Nodo.h"
#include <cmath>


class BranchAndBound
{
    private:
        vector<Nodo> nodosActivos;
        vector<float> mejorSolucion;
        float mejorCota;
        float cotaInf(Nodo nodo);
        float cotaSup(Nodo nodo);

    public:
        BranchAndBound(Simplex simplex);
        ~BranchAndBound();
        std::vector<float> solve();
        void printSolution();
};