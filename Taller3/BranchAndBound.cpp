#include "BranchAndBound.h"

using namespace std;


/*
    Metodo: Constructor
    Descripcion: este metodo crea un objeto de la clase BranchAndBound.
            utiliza un struct para comparar los problemas de la cola de prioridad.
    Parametros: no tiene.
    Retorno: El objeto creado.
*/
BranchAndBound::BranchAndBound() : problems(CompareSimplex()){}

/*
    Metodo: getBestProblem
    Descripcion: este metodo obtiene el mejor problema de la cola de prioridad.
        en caso de que el problema tenga un upperBound menor al mejor lowerBound
        se descarta y se obtiene el siguiente mejor problema.
    Parametros: no tiene.
    Retorno: El objeto creado.
*/
Simplex BranchAndBound::getBestProblem() {
    Simplex p = problems.top();
    problems.pop();
    if (p.upperBound < bestLowerBound) {
        return getBestProblem();
    }
    return p;
}

/*
    Metodo: solve
    Descripcion: este metodo resuelve el problema de optimizacion lineal
        mediante el metodo de Branch and Bound.
    Parametros: Simplex& s
    Retorno: void.
*/
void BranchAndBound::solve(Simplex& s) {
    bestLowerBound = 0.0;
    s.solve();
    s.setBasicConstraints();
    problems.push(s);

    while (!problems.empty()) {
        Simplex p = getBestProblem();

        // Se actualiza el mejor lowerBound
        if (p.lowerBound > bestLowerBound) {
            bestLowerBound = p.lowerBound;
        }

        if (p.equalBounds()) { // Si el upperBound y el lowerBound son iguales
            optimalSolution.push_back(p);
            return;
        } else if (p.isFeasible()){
            int index = 0;
            float max = 0;
            for (int i = 1; i < p.solution.size(); i++) {
                float dif = p.solution[i] - (int)p.solution[i];
                if (dif > max) {
                    max = dif;
                    index = i;
                }
            }
            //Branch
            Simplex p1 = p.copy();
            p1.insertConstraint(1, index, 3);
            Simplex p2 = p.copy();
            p2.insertConstraint(0, index, 3);
            p1.solve();
            problems.push(p1);
            p2.solve();
            problems.push(p2);
        }
    }
    cout << "No se encontró una solución óptima" << endl;
    return;
}

/*
    Metodo: printOptimalSolution
    Descripcion: este metodo imprime la solucion optima del problema.
    Parametros: no tiene.
    Retorno: void.
*/
void BranchAndBound::printOptimalSolution() {
    cout << "Solución óptima: " << endl;
    for (int i = 1; i < optimalSolution[0].solution.size(); i++) {
        cout << "x" << i << " = " << optimalSolution[0].solution[i] << " - Weight: " << optimalSolution[0].initialA[1][i] * -1 << endl;
    }
    cout << "Z = " << optimalSolution[0].solution[0] << endl;
}