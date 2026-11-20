#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Puzzle.h"

using namespace std;

int main(){
    string filename = "";
    cout << "Length: " << filename.length() << endl; // "0
    bool stateCheck = true;
    while (stateCheck == true) {
        int opcion;
        cout << "\n-----Menu Interactivo-----" << endl;
        cout << "1. Cargar Archivo" << endl;
        cout << "2. Resolver" << endl;
        cout << "3. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;
        if (opcion == 1) {
            cout << "\n-----Cargando Archivo-----" << endl;
            cout << "Nombre de archivo: ";
            cin >> filename;
            cout << "Leyendo archivo " << filename << endl;
        } else if (opcion == 2) {
            if (filename.empty() == false){
                Puzzle *p = new Puzzle(filename);
                time_t ti = clock();
                p->solve();
                time_t tf = clock();
                cout << "Tiempo de ejecucion: " << (tf-ti)/CLOCKS_PER_SEC << " segundos" << endl;
                filename = "";
            } else {
                cout << "\nPrimero debe cargar un archivo" << endl;
            }
        } else if (opcion == 3) {
            cout << "\nSaliendo..." << endl;
            stateCheck = false;
        } else {
            cout << "\nOpcion invalida" << endl;
        }
    }
    return 0;
}
