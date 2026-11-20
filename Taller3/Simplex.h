#ifndef SIMPLEX_H
#define SIMPLEX_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#define EPS 1.0e-6

using namespace std;

/*
    Descripcion de la clase Simplex:
    Esta clase representa un solucionador de problemas de optimizacion
    lineal con variables reales [x1,....,xn]., mediante el metodo Simplex. 
    este busca maximizar una funcion con restricciones asociadas.
*/
class Simplex
{
private:
    int m; // Numero de restricciones
    int n; // Numero de variables
    bool isSolved;
    int icase;
    vector<int> izrov;
    vector<int> iposv;
    //vector<float> solution;
    int simplx();
    void maxValue(int mm, vector<int> ll, int nll, int iabf, int *kp, float *bmax);
    void locatePivot(int *ip, int kp);
    void exchangeParameters(int i1, int k1, int ip, int kp);
    float fabs(float x);

public:
    vector<vector<float>> initialA; // Matriz del problema.
    vector<vector<float>> a; // Matriz en donde se genera la solucion.
    int m1; // numero de restricciones <=
    int m2; // ... >=
    int m3; // igualdad
    float upperBound;
    float lowerBound;
    vector<float> solution;

    Simplex(string file_name);
    Simplex(vector<vector<float>> a, int m1, int m2, int m3);
    ~Simplex();
    void solve(); // el retorno es [Z, x1, x2, ..., xn]
    void insertConstraint(float b, int var, int type);
    Simplex copy();
    vector<float> getSolution();
    void printProblemMatrix();
    void printSolution();

    void insertSumConstraint(float b, vector<int> vars, int type);
    void setBasicConstraints();
    bool equalBounds();
    void printSimplex();
    bool isFeasible();
};

#endif