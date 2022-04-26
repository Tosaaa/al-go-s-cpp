#include <iostream>
#include <queue>

#include "graph.hpp"

#define MAX_SIZE 7

void BFS(Graph *graph, int s);

void BFS(Graph *graph, int s) {
    vector<int> visited(graph->getNodeSize());
    queue<int> q;

    visited[s] = 1;
    q.push(s);

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        cout << v << " ";
        if (visited[v]) continue;
        visited[v] = 1;

        list<pair<GraphNode *, int>> adj = graph->bucket[v]->adj;
        for (auto it = adj.begin(); it != adj.end(); it++) {
            if (!visited[(*it).first->idx]) {
                q.push((*it).first->idx);
            }
        }
    }
    cout << endl;
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
        {INF, INF, INF, 4, 5, INF, 0}};

    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            graph->addEdge(i, j, weight[i][j]);
        }
    }
    
    BFS(graph, 0);

    delete graph;
}