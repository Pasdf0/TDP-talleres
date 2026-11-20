#include <time.h>
#include <chrono>
#include "Graph.h"

using namespace std;

int main() {
    string filename = "";
    bool stateCheck = true;
    while (stateCheck == true) {
        cout << "\n#######################################" << endl;
        int opcion;
        cout << "\n-----Menu Interactivo-----" << endl;
        cout << "1. Cargar Grafo" << endl;
        cout << "2. Buscar Clique Máximo" << endl;
        cout << "3. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;
        // OPCION 1
        if (opcion == 1) {
            cout << "\n-----Cargando Archivo-----" << endl;
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
        } 
        // OPCION 2
        else if (opcion == 2) {
            if (filename.empty() == false){
                Graph *g = new Graph(filename);
                unordered_set<int> r, x;
                unordered_set<int> p = g->getP();
                chrono::duration<double> duration;
                time_t ti = clock();
                auto start = chrono::high_resolution_clock::now();
                g->BKP(r, p, x);
                time_t tf = clock();
                auto stop = chrono::high_resolution_clock::now();
                duration = stop - start;
                cout << endl;
                cout << "Grafo: " << filename << endl;
                g->printMaxClique();
                cout << "Tiempo de ejecucion: " << duration.count() << " segundos (chrono)" << endl;
                cout << "Tiempo de ejecucion: " << (tf-ti)/CLOCKS_PER_SEC << " segundos (time.h)" << endl;
                free(g);
                cout << "\n--El archivo ha sido liberado--\n" << endl;
                filename = "";
            } else {
                cout << "\nPrimero debe cargar un archivo" << endl;
            }
        } 
        // OPCION 3
        else if (opcion == 3) {
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