#ifndef GRAPH_H_
#define GRAPH_H_

#include <climits>
#include <list>
#include <utility>
#include <vector>

#define INF INT_MAX

using namespace std;

class Graph {
   public:
    int V;
    int E;  // # of directed edges
    vector<vector<int>> adj;

    // constructor
    Graph(int _V);

    // Graph() : V(0), E(0) { nodes.clear(); }
    // Graph(int _nc, bool _d = false) : V(_nc), E(0){};
    //  copy constructor
    //  move constructor
    //  destructor

    void addNode();
    void addEdge(int v, int w, int weight);  // v->w (directed)
    bool isEdge(int v, int w);               // returns 1 if there is an edge from v to w, otherwise 0.
    void print();
    int getNodeSize();
    int getEdgeSize(bool isDirected);
};

#endif