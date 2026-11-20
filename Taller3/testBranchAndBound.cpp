#include "BranchAndBound.h"

using namespace std;

int main() {
    Simplex s = Simplex("problemTest.txt");

    BranchAndBound* b = new BranchAndBound();

    b->solve(s);

    b->printOptimalSolution();
    
    return 0;
}