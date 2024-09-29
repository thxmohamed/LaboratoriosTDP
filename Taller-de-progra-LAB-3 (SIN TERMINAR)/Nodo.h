#include "Simplex.h"

using namespace std;

class Nodo
{
private:
    Simplex simplex;
public:
    Nodo();
    Nodo(Simplex simplex);
    ~Nodo();
    Simplex getSimplex();
    void addConstraint(float b, int var, int type);
    void removeConstraint(int i);
    void printConstraints();
    //void printObjectiveFunction();
};

