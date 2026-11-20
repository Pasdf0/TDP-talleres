#ifndef BRANCHANDBOUND_H
#define BRANCHANDBOUND_H

#include <queue>
#include "Simplex.h"

using namespace std;

/*
    Clase BranchAndBound:
    Esta clase representa un solucionador de problemas de optimizacion
    lineal con variables reales [x1,....,xn]., mediante el metodo Branch and Bound. 
    este busca maximizar una funcion con restricciones asociadas.
*/

class BranchAndBound {
    private:

        // Struct para comparar los problemas de la cola de prioridad.
        struct CompareSimplex {
            bool operator()(const Simplex& s1, const Simplex& s2) const {
                if(s1.upperBound != s2.upperBound) {
                    return s1.upperBound < s2.upperBound;
                } else {
                    return s1.lowerBound > s2.lowerBound;
                }
            }
        };

        //Atributos
        vector<Simplex> optimalSolution;
        priority_queue<Simplex, vector<Simplex>, CompareSimplex> problems; // Cola de prioridad de problemas.
        float bestLowerBound; // Mejor lowerBound encontrado.

    public:
        //Metodos
        BranchAndBound();
        Simplex getBestProblem();
        void solve(Simplex& s);
        void printOptimalSolution();
        ~BranchAndBound();

};

#endif