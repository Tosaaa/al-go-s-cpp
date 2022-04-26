#include <iostream>
#include <vector>
#include "graph.hpp"

#define MAX_SIZE 7

void DFS(Graph *graph, int s);
void DFS_Util(Graph *graph, int s, vector<int> &visited);

void DFS(Graph *graph, int s) {
    vector<int> visited(graph->getNodeSize());
    DFS_Util(graph, s, visited);
    cout << endl;
    return;
}

void DFS_Util(Graph *graph, int s, vector<int> &visited) {
    visited[s] = 1;
    cout << s << " ";

    list<pair<GraphNode *, int>> adj = graph->bucket[s]->adj;
    for (auto it = adj.begin(); it != adj.end(); it++) {
        if (!visited[(*it).first->idx]) {
            DFS_Util(graph, (*it).first->idx, visited);
        }
    }
    return;
}

int main() {
    Graph *graph = new Graph(MAX_SIZE);
    int weight[MAX_SIZE][MAX_SIZE] = {
        {0, 7, INF, INF, 3, 10, INF},
        {7, 0, 4, 10, 2, 6, INF},
        {INF, 4, 0, 2, INF, INF, INF},
        {INF, 10, 2, 0, INF, 9, 4},
        {3, 2, INF, INF, 0, INF, 5},
        {10, 6, INF, 9, INF, 0, INF},
        {INF, INF, INF, 4, 5, INF, 0}
    };

    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            graph->addEdge(i, j, weight[i][j]);
        }
    }
    
    DFS(graph, 0);

    delete graph;
    
}