#include "Clique.h"
#include <ctime>
#include <fstream>

int main() {
    int option;
    while(true){
        cout << "\n####################\nMenú de ejecución\n¿Qué desea hacer?\n1. Leer un archivo\n2. Salir\n####################\nOpción: ";
        cin >> option;
        if(cin.fail()){
            cin.clear();
            cin.ignore();
            cout << "\n¡Ingrese una opción válida!\n";
            continue;}
            
        if(option == 1){
            unsigned t0, t1;
            string filename;
            cout << "Ingrese el nombre del archivo: ";
            cin >> filename;
            ifstream infile(filename);
            t0 = clock();
            if(!infile.is_open()){
                cout << "No se pudo abrir el archivo" << endl;
                return 1;
            }
            int size;
            infile >> size;
            Clique c(size);
            int u, v;
            while(infile >> u >> v){
                c.addEdge(u, v);
            }
            infile.close();

            set<int> *R = new set<int>;
            set<int> *P = new set<int>;
            set<int> *X = new set<int>;
            set<set<int>*> *C = new set<set<int>*>;
            for (int i = 0; i < size; i++) {
                P->insert(i);
            }
            C = c.BronKerbosch(R, P, X, C);

            c.printClique(C);
            t1 = clock();
            double time = (double(t1-t0)/CLOCKS_PER_SEC);
            cout << "Tiempo de ejecución: " << time << " segundos\n";

            for(auto clique : *C){
                delete clique;
            }

        }else if(option == 2){
            break;
        }else{
            cout << "\n¡Ingrese una opción válida!\n";
        }
    }

    return 0;
}