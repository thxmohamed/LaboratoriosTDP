#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#define EPS 1.0e-6

/*
    Descripcion de la clase Simplex:
    Esta clase representa un solucionador de problemas de optimizacion
    lineal con variables reales [x1,....,xn]., mediante el metodo Simplex. 
    este busca maximizar una funcion con restricciones asociadas.
*/
class Simplex
{
private:
    int restricciones; // Numero de restricciones
    int variables; // Numero de variables
    bool isSolved; // Indica si el problema ya fue resuelto.
    int icase; // Indica el estado del problema.
    std::vector<int> izrov; // Vector de indices de variables.
    std::vector<int> iposv;
    std::vector<float> solution;
    int simplx();
    void maxValue(int mm, std::vector<int> ll, int nll, int iabf, int *kp, float *bmax);
    void locatePivot(int *ip, int kp);
    void exchangeParameters(int i1, int k1, int ip, int kp);
    float fabs(float x);

public:
    std::vector<std::vector<float>> initialA; // Matriz del problema.
    std::vector<std::vector<float>> matrizSol; // Matriz en donde se genera la solucion.
    int restriccionesMenor; // numero de restricciones <=
    int restriccionesMayor; // ... >=
    int restriccionesIgual; // igualdad

    Simplex();
    Simplex(std::string file_name);
    Simplex(std::vector<std::vector<float>> matrizSol, int restriccionesMenor, int restriccionesMayor, int restriccionesIgual);
    ~Simplex();
    bool isFeasible();
    float getZ();
    int getPivotColumn();
    std::vector<float> solve(); // el retorno es [Z, x1, x2, ..., xn]
    void insertConstraint(float b, int var, int type);
    Simplex copy();
    std::vector<float> getSolution();
    void printProblemMatrix();
    void printSolution();
    void insertObjectiveFunction(std::vector<float> objFunction);
};