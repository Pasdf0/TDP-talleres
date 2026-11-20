#include "Graph.h"

/*
 * Method: Constructor->Graph
 * Description: This method initializes the graph from a number of vertices
 *            and creates an adjacency matrix with all values set to false.
 * Parameters: 
 *      -numVertices: Number of Vertices in the graph.
 * Return: void
*/
Graph::Graph(int numVertices) {
    this->numVertices = numVertices;
    adjMatrix = new bool*[numVertices];
    for (int i = 0; i < numVertices; i++) {
        adjMatrix[i] = new bool[numVertices];
        for (int j = 0; j < numVertices; j++) {
            adjMatrix[i][j] = false;
        }
    }
}

/*
 * Method: Constructor->Graph
 * Description: This method initializes the graph from a text file containing the 
 *          number of vertices and the edges of the graph. Also sets a list of degrees for each
 *          vertex and a list of neighbours for each vertex.
 * Parameters:
 *      -filename: Name of the file containing the graph.
 * Return: void
*/
Graph::Graph(string filename) {
    ifstream file;
    file.open(filename, ios::in);
    if (!file.is_open()) {
        cout << "Error: File not found" << endl;
        return;
    }
    // Read number of vertices
    int numVertices;
    file >> numVertices;
    this->numVertices = numVertices;
    // Initialize adjacency matrix
    adjMatrix = new bool*[numVertices];
    for (int i = 0; i < numVertices; i++) {
        adjMatrix[i] = new bool[numVertices];
        for (int j = 0; j < numVertices; j++) {
            adjMatrix[i][j] = false;
        }
    }
    // Read edges
    string line;
    getline(file, line);
    while (getline(file, line)) {
        istringstream iss(line);
        int i, j;
        if (!(iss >> i >> j)) {
            cerr << "Invalid input format\n";
            return;
        }
        addEdge(i, j);
    }
    file.close();
    // Set degrees and neighbours
    setDegrees_Neighbours();
}

/*
 * Method: addEdge
 * Description: This method adds an edge between two vertices in the graph.
 * Parameters:
 *     -i: Vertex i
 *     -j: Vertex j
 * Return: void
*/
void Graph::addEdge(int i, int j) {
    adjMatrix[i][j] = true;
    adjMatrix[j][i] = true;
    return;
}

/*
 * Method: setDegrees_Neighbours
 * Description: This method sets the Degrees List and Neighbours List of lists attributes 
 *          of the graph.
 * Parameters: void
 * Return: void
*/
void Graph::setDegrees_Neighbours() {
    Degrees = new int[numVertices];
    Neighbours = vector<unordered_set<int>>(numVertices);
    for (int i = 0; i < numVertices; i++) {
        int degree = 0;
        for (int j = 0; j < numVertices; j++) {
            if (adjMatrix[i][j]) {
                degree++;
                Neighbours[i].insert(j);
            }
        }
        Degrees[i] = degree;
    }
}

/*
 * Method: getP
 * Description: This method returns a set with all the vertices in the graph.
 * Parameters: void
 * Return: set<int> with all the vertices in the graph.
*/
unordered_set<int> Graph::getP() {
    unordered_set<int> p;
    for (int i = 0; i < numVertices; i++) {
        p.insert(i);
    }
    return p;
}

/*
 * Method: minus
 * Description: This method returns a copy of the first set without the elements
 *          of the second set.
 * Parameters:
 *      -a: Set a
 *      -b: Set b
 * Return: set<int> with the elements of a that are not in b
*/
unordered_set<int> Graph::minus(unordered_set<int>& a, unordered_set<int>& b) {
    unordered_set<int> result;
    for (int v : a){
        if (b.find(v) == b.end()){
            result.insert(v);
        }
    }
    return result;
}

/*
 * Method: intersection
 * Description: This method returns the intersection of two sets.
 * Parameters:
 *     -a: Set a
 *     -b: Set b
 * Return: set<int> with the intersection of a and b.
*/
unordered_set<int> Graph::intersection(unordered_set<int>& a, unordered_set<int>& b) {
    unordered_set<int> result;
    if (a.size() < b.size()) {
        for (int v : a) {
            if (b.find(v) != b.end()) {
                result.insert(v);
            }
        }
    } else {
        for (int v : b) {
            if (a.find(v) != a.end()) {
                result.insert(v);
            }
        }
    }
    return result;
}

/*
 * Method: BKP
 * Description: This method is the Bron-Kerbosch-Pivot algorithm to find the maximum clique in the graph.
 * Parameters:
 *     -r: Set r
 *     -p: Set p
 *     -x: Set x
 * Return: void (The maximum clique is stored in the maxClique attribute)
*/
void Graph::BKP(unordered_set<int>& r, unordered_set<int>& p, unordered_set<int>& x) {
    if (p.empty() && x.empty()) {
        if (r.size() > maxClique.size()) {
            maxClique = r; // Update maxClique
        }
        return;
    }
    // Get optimal pivot
    int pivot = getOptimalPivot(p);
    if (pivot == -1) {
        return;
    }
    unordered_set<int> pTemp = minus(p, Neighbours[pivot]);
    for (int v : pTemp) {
        unordered_set<int> r1 = r;
        r1.insert(v);

        unordered_set<int> p1 = intersection(p, Neighbours[v]);
        unordered_set<int> x1 = intersection(x, Neighbours[v]);

        BKP(r1, p1, x1);
        p.erase(v);
        x.insert(v);
    }
    return;
}

/*
 * Method: getOptimalPivot
 * Description: This method returns the optimal pivot for the Bron-Kerbosch-Pivot algorithm.
 *          The optimal pivot is the vertex with the highest degree in the set p.
 * Parameters:
 *     -p: Set p
 * Return: int with the optimal pivot.
*/
int Graph::getOptimalPivot(unordered_set<int>& p) {
    int pivot = -1;
    int maxDegree = -1;
    for (int v : p) {
        if (Degrees[v] > maxDegree) {
            pivot = v;
            maxDegree = Degrees[v];
        }
    }
    return pivot;
}

//Prints for debug and results

/*
 * Method: printGraph
 * Description: This method prints the adjacency matrix of the graph.
 * Parameters: void
 * Return: void
*/
void Graph::printGraph() {
    cout << "Graph: " << this->numVertices << " vertices" << endl;
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

/*
 * Method: printEdges
 * Description: This method prints the edges of the graph as it would be read from a file.
 * Parameters: void
 * Return: void
*/
void Graph::printEdges() {
    cout << "Graph: " << this->numVertices << " vertices" << endl;
    for (int i = 0; i < numVertices; i++) {
        for (int j = i; j < numVertices; j++) {
            if (adjMatrix[i][j]) {
                cout << i << " " << j << endl;
            }
        }
    }
    cout << endl;
}

/*
 * Method: printMaxClique
 * Description: This method prints the maximum clique found in the graph with its size.
 * Parameters: void
 * Return: void
*/
void Graph::printMaxClique() {
    set<int> maxCliqueOrdered;
    for (int v : maxClique) {
        maxCliqueOrdered.insert(v);
    }
    cout << "Max Clique: ";
    for (int v : maxCliqueOrdered) {
        cout << v << " ";
    }
    cout << endl;
    cout << "Tamaño del clique: " << maxCliqueOrdered.size() << endl << endl;
}

/*
 * Method: printDegrees
 * Description: This method prints the degrees of each vertex in the graph.
 * Parameters: void
 * Return: void
*/
void Graph::printDegrees() {
    cout << "Degrees: " << endl;
    for (int i = 0; i < numVertices; i++) {
        cout << "El nodo " << i << " tiene " << Degrees[i] << " grados" << endl;
    }
    cout << endl << endl;
}