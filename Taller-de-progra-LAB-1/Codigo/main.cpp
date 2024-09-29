#include "Puzzle.h"
#include <ctime>

using namespace std;

int main() {
    int choice;
    while(true) {
        cout << "Menú de ejecución\n¿Qué desea hacer?\n1. Resolver puzzle\n2. Salir\n";
        cin >> choice;
        if(choice == 1) {
            unsigned t0, t1;

            cout << "Nombre de archivo: ";
            string filename;
            cin >> filename;

            t0 = clock();

            Puzzle *p = new Puzzle(filename);
            p->solve();

            t1 = clock();

            double time = (double(t1-t0)/CLOCKS_PER_SEC);
            cout << "Tiempo de ejecución: " << time << endl;
            
        } else if(choice == 2) {
            break;
        } else {
            cout << "#################\n¡Opción inválida!\n#################\n";
        }
    }
    return 0;
}