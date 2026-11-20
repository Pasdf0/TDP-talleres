#ifndef Graph_h
#define Graph_h

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <unordered_set>

using namespace std;

class Graph {
    private:
        int numVertices;
        bool** adjMatrix;
        int* Degrees; // Grados de los vértices
        vector<unordered_set<int>> Neighbours; // Vecinos de los vértices
        unordered_set<int> maxClique;
    public:
        // Constructores
        Graph(int numVertices);
        Graph(string filename);

        // Métodos relativos a la creación del grafo
        void addEdge(int i,int j);
        void setDegrees_Neighbours();
        
        // Métodos relativos a la solución
        unordered_set<int> getP(); // Devuelve un conjunto con todos los vértices
        unordered_set<int> minus(unordered_set<int>& a, unordered_set<int>& b);
        unordered_set<int> intersection(unordered_set<int>& a, unordered_set<int>& b);
        void BKP(unordered_set<int>& r, unordered_set<int>& p, unordered_set<int>& x); // Bron-Kerbosch-Pivot
        int getOptimalPivot(unordered_set<int>& p);
        
        // Prints para debug y entrega de resultados
        void printGraph();
        void printEdges();
        void printMaxClique();
        void printDegrees();
};

#endif // Graph_h