#include "Simplex.h"

Simplex::Simplex(){}

/*
    Metodo: Constructor
    Descripcion: este metodo permite iniciar un Simplex, recibiendo
        el nombre de un archivo, el cual contendra los datos necesarios
        para la creacion de el Simplex.
    Parametros:
        -filename: nombre del archivo que contendra los datos.
    Retorno: El objeto creado.
*/
Simplex::Simplex(std::string fileName)
{
    std::string line;
    std::fstream txtStream(fileName);
    std::stringstream charStream;
    std::string stringNumber;

    if (!txtStream.is_open())
    {
        throw std::invalid_argument("El archivo ingresado no existe.");
    }

    getline(txtStream, line);
    charStream << line;
    getline(charStream, stringNumber, ' ');
    this->restriccionesMenor = stoi(stringNumber);
    getline(charStream, stringNumber, ' ');
    this->restriccionesMayor = stoi(stringNumber);
    getline(charStream, stringNumber, ' ');
    this->restriccionesIgual = stoi(stringNumber);

    while (getline(txtStream, line))
    {
        charStream.clear();
        charStream << line;
        std::vector<float> function;
        while (getline(charStream, stringNumber, ' '))
        {
            function.push_back(stof(stringNumber));
        }
        this->matrizSol.push_back(function);
    }
    this->variables = matrizSol[0].size() - 1;
    this->restricciones = restriccionesMenor + restriccionesMayor + restriccionesIgual;
    if (restricciones != (int)matrizSol.size() - 1)
    {
        throw std::invalid_argument("El numero de restricciones ingresados no coincide con la matriz dada.");
    }

    for (int i = 1; i <= restricciones; i++)
    {
        if (matrizSol[i][0] < 0.0 || (int)matrizSol[i].size() != variables + 1)
        {
            // Error al crear el Simplex, ya que no se permiten
            // constantes negativas para las restricciones, o el
            // numero de columnas no coincide para todas las filas.
            throw std::invalid_argument("La matriz ingresada no es valida.");
        }
    }

    std::vector<float> function;
    for (int i = 0; i <= variables; i++)
    {
        function.push_back(0.0);
    }

    this->matrizSol.push_back(function);
    this->initialA = matrizSol;
    this->isSolved = false;
    txtStream.close();
}

/*
    Metodo: Constructor
    Descripcion: este metodo permite iniciar un Simplex, recibiendo
        los datos necesarios para la creacion de este.
    Parametros:
        -matrizSol: Matriz con los valores que acompanian a la funcion a maximizar
            y a las restricciones del problema a resolver.
        -restriccionesMenor: numero de restricciones de tipo 1 (<=)
        -restriccionesMayor: numero de restricciones de tipo 2 (>=)
        -restriccionesIgual: numero de restricciones de tipo 3 (==)
    Retorno: El objeto creado.
*/
Simplex::Simplex(std::vector<std::vector<float>> matrizSol, int restriccionesMenor, int restriccionesMayor, int restriccionesIgual)
{
    int restricciones = restriccionesMenor + restriccionesMayor + restriccionesIgual;
    for (int i = 1; i <= restricciones; i++)
    {
        if (matrizSol[i][0] < 0.0)
        {
            // Error al crear el Simplex, ya que no se permiten
            // constantes negativas para las restricciones.
            throw std::invalid_argument("La matriz ingresada no es valida.");
        }
    }

    this->initialA = matrizSol;
    this->matrizSol = matrizSol;
    this->restriccionesMenor = restriccionesMenor;
    this->restriccionesMayor = restriccionesMayor;
    this->restriccionesIgual = restriccionesIgual;
    this->restricciones = restricciones;
    this->variables = matrizSol[0].size() - 1;
    this->isSolved = false;
}

/*
    Descripcion: este metodo permite eliminar el objeto.
    Parametros: no posee.
    Retorno: no posee.
*/
Simplex::~Simplex()
{
}

/*
    Descripcion: este metodo permite resolver el problema de programacion
        lineal invocando al metodo de simplex.
    Parametros: No posee.
    Retorno: 
       -Si encuntra solucion: Arreglo con el valor maximizado y los 
        valores de los parametros de la funcion a maximizar.
       -Si NO encuntra solucion: Arreglo vacio.

*/
std::vector<float> Simplex::solve()
{
    icase = simplx();
    isSolved = true;
    if (icase != 0)
    {
        std::vector<float> emptyVector;
        return emptyVector; // No hay solucion
    }

    std::vector<float> parameters(variables + 1, 0.0);
    parameters[0] = matrizSol[0][0];
    for (int i = 0; i < restricciones; i++)
    {
        if (iposv[i] < variables)
        {
            parameters[iposv[i] + 1] = matrizSol[i + 1][0];
        }
    }
    solution = parameters;

    return parameters;
}

/*
    Descripcion: este metodo resuelve el problema de maximizacion
        dado la funcion y las restricciones dadas en la creacion
        del objeto, todo mediante el metodo simplex.
    Parametros: No posee.
    Retorno:
        - 0: Fue posible resolver el problema.
        - 1: No existe un limite para la funcion a maximizar.
        - -1: No existe solucion que cumpla con las restricciones dadas.
*/
int Simplex::simplx()
{
    int i, ip, is, k, kh, kp, nl1;
    float q1, bmax;

    // se declaran dos vectores para guardar las posiciones de las variables
    std::vector<int> l1; // l1: vector con las posiciones de las variables
    std::vector<int> l3; // l3: vector con las posiciones de las restricciones de tipo 2 (>=)
    nl1 = variables;    // nl1: largo del vector l1
    izrov.clear();     // izrov: vector con las posiciones de las variables
    iposv.clear();    // iposv: vector con las posiciones de las restricciones de tipo 2 (>=)
    for (k = 0; k < variables; k++) 
    {
        l1.push_back(k);
        izrov.push_back(k);
    }
    for (i = 0; i < restricciones; i++)
    {
        iposv.push_back(variables + i);
    }

    if (restriccionesMayor + restriccionesIgual)
    {
        for (i = 0; i < restriccionesMayor; i++)
        {
            l3.push_back(1);
        }
        for (k = 0; k < variables + 1; k++)
        {
            q1 = 0.0;
            for (i = restriccionesMenor; i < restricciones; i++)
            {
                q1 += matrizSol[i + 1][k];
            }
            matrizSol[restricciones + 1][k] = -q1;
        }
        for (;;)
        {
            maxValue(restricciones + 1, l1, nl1, 0, &kp, &bmax);
            if (bmax <= EPS && matrizSol[restricciones + 1][0] < -EPS)
            {
                return -1; // icase -1
            }
            else if (bmax <= EPS && matrizSol[restricciones + 1][0] <= EPS)
            {
                for (ip = restriccionesMenor + restriccionesMayor; ip < restricciones; ip++)
                {
                    if (iposv[ip] == ip + variables)
                    {
                        maxValue(ip, l1, nl1, 1, &kp, &bmax);
                        if (bmax > EPS)
                        {
                            goto one;
                        }
                    }
                }
                for (i = restriccionesMenor; i < restriccionesMenor + restriccionesMayor; i++)
                {
                    if (l3[i - restriccionesMenor] == 1)
                    {
                        for (k = 0; k < variables + 1; k++)
                        {
                            matrizSol[i + 1][k] = -matrizSol[i + 1][k];
                        }
                    }
                }
                break;
            }
            locatePivot(&ip, kp);
            if (ip == -1)
            {
                return -1; // icase -1
            }
        one:
            exchangeParameters(restricciones + 1, variables, ip, kp);
            if (iposv[ip] >= (variables + restriccionesMenor + restriccionesMayor))
            {
                for (k = 0; k < nl1; k++)
                {
                    if (l1[k] == kp)
                    {
                        break;
                    }
                }
                --nl1;
                for (is = k; is < nl1; is++)
                {
                    l1[is] = l1[is + 1];
                }
            }
            else
            {
                kh = iposv[ip] - restriccionesMenor - variables;
                if (kh >= 0 && l3[kh])
                {
                    l3[kh] = 0;
                    ++matrizSol[restricciones + 1][kp + 1];
                    for (i = 0; i < restricciones + 2; i++)
                    {
                        matrizSol[i][kp + 1] = -matrizSol[i][kp + 1];
                    }
                }
            }
            is = izrov[kp];
            izrov[kp] = iposv[ip];
            iposv[ip] = is;
        }
    }

    for (;;)
    {
        maxValue(0, l1, nl1, 0, &kp, &bmax);
        if (bmax <= EPS)
        {
            return 0; // icase = 0
        }
        locatePivot(&ip, kp);
        if (ip == -1)
        {
            return 1; // icase  = 1
        }
        exchangeParameters(restricciones, variables, ip, kp);
        is = izrov[kp];
        izrov[kp] = iposv[ip];
        iposv[ip] = is;
    }
}

/*
    Descripcion: este metodo calcula el valor mayor de los elementos
        de la fila mm, cuyo indice esta en el vector ll dado (corrido en 1 posicion
        ya que el primer elemento corresponde a una constante y los valores se
        estan guardando en base a los parametros x1, x2 ...), guardando el valor
        en bmax y el indice en kp, esto considerando el valor absoluto del valor
        si se entrega iabf distinto de 0, en otro caso se toma el valor tal cual.
    Parametros:
        -mm: fila a revisar de la matriz.
        -ll: vector con las posciones de la columna a revisar en la matriz.
        -nll: largo del vector ll
        -iabf: valor que indica si se desea calcular con el valor absoluto o no.
        -kp: direccion donde se guardara la posicion del elemento con mayor valor.
        -bmax: direccion donde se guardara el valor maximo encontrado.
    Retorno: No posee.
*/
void Simplex::maxValue(int mm, std::vector<int> ll, int nll, int iabf, int *kp, float *bmax)
{
    int k;
    float test;

    if (nll <= 0)
    {
        *bmax = 0.0;
    }
    else
    {
        *kp = ll[0];
        *bmax = matrizSol[mm][*kp + 1];
        for (k = 1; k < nll; k++)
        {
            if (iabf == 0)
            {
                test = matrizSol[mm][ll[k] + 1] - (*bmax);
            }
            else
            {
                test = fabs(matrizSol[mm][ll[k] + 1]) - fabs(*bmax);
            }

            if (test > 0.0)
            {
                *bmax = matrizSol[mm][ll[k] + 1];
                *kp = ll[k];
            }
        }
    }
}

/*
    Descripcion: este metodo encuentra la fila en donde se
        encuentra el elemento que sirve como pivote.
    Parametros:
        -ip: direccion donde se guardara la fila del elemento pivote.
        -kp: numero de la columna en donde encontrar el pivote.
    Retorno: No posee.
*/
void Simplex::locatePivot(int *ip, int kp)
{

    int k, i;
    float qp, q0, q, q1;

    kp = kp + 1;
    *ip = -1;
    for (i = 0; i < restricciones; i++)
    {
        if (matrizSol[i + 1][kp] < -EPS)
        {
            break;
        }
    }

    if (i + 1 > restricciones)
    {
        return;
    }

    q1 = -matrizSol[i + 1][0] / matrizSol[i + 1][kp];
    *ip = i;
    for (i = *ip + 1; i < restricciones; i++)
    {
        if (matrizSol[i + 1][kp] < -EPS)
        {
            q = -matrizSol[i + 1][0] / matrizSol[i + 1][kp];
            if (q < q1)
            {
                *ip = i;
                q1 = q;
            }
            else if (q == q1)
            {
                qp = -1;
                q0 = -1;
                for (k = 0; k < variables; k++)
                {
                    qp = -matrizSol[*ip + 1][k + 1] / matrizSol[*ip + 1][kp];
                    q0 = -matrizSol[i + 1][k + 1] / matrizSol[i + 1][kp];
                    if (q0 != qp)
                    {
                        break;
                    }
                }
                if (q0 < qp)
                {
                    *ip = i;
                }
            }
        }
    }
}

/*
    Descripcion: este metodo realiza operaciones matriciales, para
        intercambiar un parametro perteneciente a la restricciones restriccionesIgual
        con los parametros restantes.
    Parametros:
        -i1: numero de filas a explorar.
        -k1: numero de columnas a explorar.
        -ip: numero de la fila del pivote.
        -kp: numero de la columna del pivote.
    Retorno: No posee.
*/
void Simplex::exchangeParameters(int i1, int k1, int ip, int kp)
{
    int kk, ii;
    float piv;

    piv = 1.0 / matrizSol[ip + 1][kp + 1];
    for (ii = 0; ii < i1 + 1; ii++)
    {
        if (ii - 1 != ip)
        {
            matrizSol[ii][kp + 1] *= piv;
            for (kk = 0; kk < k1 + 1; kk++)
            {
                if (kk - 1 != kp)
                {
                    matrizSol[ii][kk] -= matrizSol[ip + 1][kk] * matrizSol[ii][kp + 1];
                }
            }
        }
    }

    for (kk = 0; kk < k1 + 1; kk++)
    {
        if (kk - 1 != kp)
        {
            matrizSol[ip + 1][kk] *= -piv;
        }
    }

    matrizSol[ip + 1][kp + 1] = piv;
}

/*
    Descripcion: este metodo calcula el valor absoluto de un
        valor dado.
    Parametros:
        -x: valor a calcular el valor absoluto
    Retorno: valor absoluto de x.
*/
float Simplex::fabs(float x)
{
    if (x < 0.0)
    {
        return x * -1.0;
    }

    return x;
}

/*
    Descripcion: este metodo permite insertar una restriccion
        a la matriz que representa el problema.
    Parametros:
        -b: valor constante de la restriccion.
        -var: variable/parametro a la que se agrega la restriccion
        -type: tipo de la restriccion, este puede ser:
            .1: var <= b
            .2: var >= b
            .3: var == b
    Retorno: No posee.
*/
void Simplex::insertConstraint(float b, int var, int type)
{
    if (var == 0 || var > variables || b < 0.0)
    {
        return;
    }

    std::vector<float> constraint(variables + 1, 0.0);
    constraint[0] = b;
    constraint[var] = -1.0;

    switch (type)
    {
    case 1: // var <= b
        this->initialA.insert(this->initialA.begin() + restriccionesMenor + 1, constraint);
        restriccionesMenor++;
        break;
    case 2: // var >= b
        this->initialA.insert(this->initialA.begin() + restriccionesMenor + restriccionesMayor + 1, constraint);
        restriccionesMayor++;
        break;
    case 3: // var == b
        this->initialA.insert(this->initialA.begin() + restricciones + 1, constraint);
        restriccionesIgual++;
        break;
    default:
        return;
        break;
    }
    restricciones++;
    isSolved = false;
    matrizSol = initialA;
    solution.clear();
}

/*
    Descripcion: este metodo permite copiar el objeto con sus
        respectivos valores.
    Parametros: No tiene.
    Retorno: El objeto creado con los valores
        del objeto copiado.
*/
Simplex Simplex::copy()
{
    Simplex s = Simplex(initialA, restriccionesMenor, restriccionesMayor, restriccionesIgual);
    s.izrov = this->izrov;
    s.iposv = this->iposv;
    s.isSolved = this->isSolved;
    s.icase = this->icase;
    s.matrizSol = this->matrizSol;
    s.solution = this->solution;
    return s;
}

std::vector<float> Simplex::getSolution()
{
    if (isSolved && icase == 0)
    {
        return solution;
    }
    std::vector<float> empty;
    return empty;
}

/*
    Descripcion: este metodo permite imprimir la matriz
        que representa al problema.
    Parametros: No tiene.
    Retorno: No tiene.
*/
void Simplex::printProblemMatrix()
{
    for (std::size_t i = 0; i < initialA.size(); i++)
    {
        for (std::size_t j = 0; j < initialA[0].size(); j++)
        {
            std::string aij = std::to_string(initialA[i][j]);
            aij = aij.substr(0, aij.find(".") + 3);
            aij.insert(aij.begin(), 10 - aij.length(), ' ');
            std::cout << aij;
        }
        std::cout << std::endl;
    }
}

/*
    Descripcion: este metodo permite imprimir la matriz solucion,
        esto si es que fue resuelto en problema.
    Parametros: No tiene.
    Retorno: No tiene.
*/
void Simplex::printSolution()
{
    if (isSolved)
    {
        int nm1m2;
        if (icase == 1)
        {
            std::cout << "No existe limite para la funcion a maximizar." << std::endl;
        }
        else if (icase == -1)
        {
            std::cout << "No hay solucion que cumpla con las restricciones." << std::endl;
        }
        else
        {
            nm1m2 = variables + restriccionesMenor + restriccionesMayor;
            std::string txt[nm1m2];
            for (int i = 0; i < variables; i++)
            {
                txt[i] = "x" + std::to_string(i + 1);
            }
            for (int i = variables; i < nm1m2; i++)
            {
                txt[i] = "y" + std::to_string(i + 1 - variables);
            }

            std::cout << std::string(11, ' ');
            for (int i = 0; i < variables; i++)
            {
                if (izrov[i] < nm1m2)
                {
                    txt[izrov[i]].insert(txt[izrov[i]].begin(), 10 - txt[izrov[i]].length(), ' ');
                    std::cout << txt[izrov[i]];
                }
            }

            std::cout << std::endl;
            for (int i = 0; i < restricciones + 1; i++)
            {
                if (i == 0 || iposv[i - 1] < nm1m2)
                {
                    if (i > 0)
                    {
                        std::cout << txt[iposv[i - 1]];
                    }
                    else
                    {
                        std::cout << "  ";
                    }

                    std::string ai0 = std::to_string(matrizSol[i][0]);
                    ai0 = ai0.substr(0, ai0.find(".") + 3);
                    ai0.insert(ai0.begin(), 10 - ai0.length(), ' ');
                    std::cout << ai0;
                    for (int j = 1; j < variables + 1; j++)
                    {
                        if (izrov[j - 1] < nm1m2)
                        {
                            std::string aij = std::to_string(matrizSol[i][j]);
                            aij = aij.substr(0, aij.find(".") + 3);
                            aij.insert(aij.begin(), 10 - aij.length(), ' ');
                            std::cout << aij;
                        }
                    }
                    std::cout << std::endl;
                }
            }
        }
    }
    else
    {
        std::cout << "No esta resuelto." << std::endl;
    }
}

/*
    Descripcion: este metodo permite verificar si el problema
        es factible.
    Parametros: No tiene.
    Retorno: true si es factible, false en otro caso.
*/

bool Simplex::isFeasible()
{
    if (isSolved && icase == 0)
    {
        return true;
    }
    return false;
}

/*
    Descripcion: este metodo permite obtener el valor de la funcion
        objetivo.
    Parametros: No tiene.
    Retorno: valor de la funcion objetivo.
*/

float Simplex::getZ()
{
    if (isSolved && icase == 0)
    {
        return matrizSol[0][0];
    }
    return 0.0;
}

/*
    Descripcion: este metodo permite obtener el valor de la columna
        pivote.
    Parametros: No tiene.
    Retorno: valor de la columna pivote.
*/

int Simplex::getPivotColumn()
{
    if (isSolved && icase == 0)
    {
        return iposv[0];
    }
    return -1;
}

/*
    Descripcion: este metodo permite insertar la funcion objetivo
        al problema.
    Parametros:
        -objFunction: vector con los valores de la funcion objetivo.
    Retorno: No tiene.
*/

void Simplex::insertObjectiveFunction(std::vector<float> objFunction)
{
    if (objFunction.size() != variables + 1)
    {
        return;
    }

    for (int i = 0; i < variables + 1; i++)
    {
        matrizSol[0][i] = objFunction[i];
    }
    isSolved = false;
    solution.clear();
}