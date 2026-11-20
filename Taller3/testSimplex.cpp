#include "Simplex.h"

using namespace std;

int main() {
    Simplex s = Simplex("problemTest.txt");
    s.solve();
    s.printProblemMatrix();
    cout << endl;
    s.printSimplex();
}