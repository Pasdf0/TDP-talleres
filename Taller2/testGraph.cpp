#include "Graph.h"

using namespace std;

/*
Grafo de prueba:
7     -Vertices
0 1     -Aristas
0 2
0 3
0 5
1 2
1 4
1 6
2 3
2 4
3 4
3 5
3 6
4 5
4 6
5 6
*/

int main() {
    // Create Graph
    Graph* g = new Graph(7);
    // Edges  (a,b)
    int a[15] = {0,0,0,0,1,1,1,2,2,3,3,3,4,4,5}; 
    int b[15] = {1,2,3,5,2,4,6,3,4,4,5,6,5,6,6};
    for (int i = 0; i < 15; i++) {
        g->addEdge(a[i],b[i]);
    }
    // Set degrees and neighbours
    g->setDegrees_Neighbours();

    // Print Graph
    cout << "-Grafo leído: " << endl;
    g->printEdges();

    // Print Adjacency Matrix
    cout << "-Matriz de adyacencia: " << endl;
    g->printGraph();

    // Print Degrees
    cout << "-Grados de los vértices: " << endl;
    g->printDegrees();

    // Print Maximum Clique
    cout << "-Clique Máximo: " << endl;
    unordered_set<int> r,x;
    unordered_set<int> p = g->getP();
    g->BKP(r, p, x);
    g->printMaxClique();

    return 0;
}