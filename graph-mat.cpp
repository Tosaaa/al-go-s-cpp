// graph based on adjacency mat

#include "graph-mat.hpp"

#include <iostream>

// constructor
Graph::Graph(int _V) {
    V = _V;
    E = 0;
    adj.resize(V);
    for (int i = 0; i < V; i++) {
        adj[i].resize(V);
        for (int j = 0; j < V; j++) {
            if (i != j) adj[i][j] = INF;
            else adj[i][j] = 0;
        }
    }
}

// void Graph::addNode() {
//     bucket.push_back(new GraphNode(V++));
// }

void Graph::addEdge(int v, int w, int weight) {
    if (v >= V || w >= V || v < 0 || w < 0) return;
    if (weight == INF || weight == 0) return;
    E++;
    if (adj[v][w] == INF)
        adj[v][w] = weight;
    else
        adj[v][w] += weight;
}

bool Graph::isEdge(int v, int w) {
    if (v >= V || w >= V || v < 0 || w < 0) return false;
    if (adj[v][w] > 0 && adj[v][w] < INF) return true;
    return false;
}

void Graph::print() {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (adj[i][j] == INF)
                cout << "- ";
            else
                cout << adj[i][j] << " ";
        }
        cout << endl;
    }
}

int Graph::getNodeSize() {
    return V;
}

int Graph::getEdgeSize(bool isDirected) {
    return isDirected ? E : E / 2;
}

// int main() {
//     Graph *graph = new Graph(5);
//     graph->addEdge(0, 1, 1);
//     graph->addEdge(0, 2, 4);
//     graph->addEdge(3, 0, 2);
//     graph->addEdge(4, 1, 3);
//     graph->print();
//     cout << graph->isEdge(0, 1) << endl;
//     cout << graph->isEdge(0, 2) << endl;
//     cout << graph->isEdge(0, 3) << endl;
//     delete graph;
//     return 0;
// }