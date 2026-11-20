#include <chrono>
#include "Graph.h"

/*
 * Este testMain es principalmente para probar la velocidad de ejecución del algoritmo
 * Bron-Kerbosch-Pivot en un grafo sin tener que pasar por el menú del main.
 * Es un test no solicitado pero fue de utilidad en el testeo del algoritmo
 * por lo que se decidió dejarlo en la entrega.
 * 
 * Este archivo tiene un apartado en el makefile pero no está en el "make all:"
*/

int main() {
    Graph* g = new Graph("grafo32.txt"); //Nombre del Archivo o directorio
    unordered_set<int> r;
    unordered_set<int> p = g->getP();
    unordered_set<int> x;

    chrono::duration<double> duration;
    // Start chrono
    auto start = chrono::high_resolution_clock::now();
    g->BKP(r, p, x);
    auto stop = chrono::high_resolution_clock::now();
    // Stop chrono
    duration = stop - start;


    g->printMaxClique();
    cout << "Tiempo de ejecucion: " << duration.count() << " segundos (chrono)" << endl;
}