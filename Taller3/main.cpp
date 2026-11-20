#include <iostream>
#include <chrono>
#include "BranchAndBound.h"

using namespace std;

int main() {
    string filename = "";
    bool stateCheck = true;
    while (stateCheck == true) {
        cout << "\n#######################################" << endl;
        int opcion;
        cout << "\n-----Menu Interactivo-----" << endl;
        cout << "1. Calcular knapsack problem" << endl;
        cout << "2. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;
        // OPCION 1
        if (opcion == 1) {
            cout << "\n-----Seleccionando Archivo-----" << endl;
            cout << "Nombre de archivo: ";
            cin >> filename;
            cout << "\nLeyendo archivo " << filename << "...\n" << endl;
            ifstream file;
            file.open(filename, ios::in);
            if (file.is_open() == false) {
                cout << "### Error: Archivo no encontrado ###" << endl;
                filename = "";
            } else {
                cout << "Archivo cargado exitosamente" << endl;
            }
            cout << "\n\n --Solucionando problema-- " << endl;
            if (filename.empty() == false){
                // Solucion de problema
                Simplex s = Simplex(filename);

                BranchAndBound* b = new BranchAndBound();

                chrono::duration<double> time_span;
                auto start = chrono::high_resolution_clock::now();
                b->solve(s);
                auto end = chrono::high_resolution_clock::now();

                b->printOptimalSolution();
                time_span = chrono::duration_cast<chrono::duration<double>>(end - start);
                cout << "Tiempo de ejecución: " << time_span.count() << " segundos" << endl;
            } else {
                cout << "\nPrimero debe cargar un archivo" << endl;
            }
        } 
        // OPCION 3
        else if (opcion == 2) {
            cout << "\nSaliendo..." << endl;
            stateCheck = false;
        } 
        // OPCION INVALIDA
        else {
            cout << "\nOpcion invalida" << endl;
            return 0;
        }
        cout << "\n#######################################" << endl;
    }
    return 0;
}