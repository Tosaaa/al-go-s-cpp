#include <iostream>
#include <queue>
#include <stack>

#include "graph.hpp"

#define MAX_SIZE 7

void dijkstra(Graph *graph, int s, vector<int> &dst);
void dijkstra_path(Graph *graph, int s, int e, vector<int> &dst);

void dijkstra(Graph *graph, int s, vector<int> &dst) {
    int V = graph->getNodeSize();
    vector<int> visited(V);
    vector<int> d(V, INF);  // storing distances.
    d[s] = 0;
    priority_queue<pair<int, int>> q;
    q.push({0, s});

    while (!q.empty()) {
        // extract min
        int min = q.top().second;
        q.pop();
        if (visited[min]) continue;
        // when the given graph is not connected graph: how ?

        visited[min] = 1;

        // update distance
        list<pair<GraphNode *, int>> adj = graph->bucket[min]->adj;
        for (auto it = adj.begin(); it != adj.end(); it++) {
            if (d[min] + (*it).second < d[(*it).first->idx]) {
                d[(*it).first->idx] = d[min] + (*it).second;
                q.push({-d[(*it).first->idx], (*it).first->idx});
            }
        }
    }

    for (int i = 0; i < V; i++)
        dst[i] = d[i];

    return;
}

void dijkstra_path(Graph *graph, int s, int e, vector<int> &dst) {
    int V = graph->getNodeSize();
    vector<int> visited(V, 0);
    vector<int> p(V, -1);
    vector<int> d(V, INF);  // storing distances.
    d[s] = 0;
    stack<int> path_stack;
    priority_queue<pair<int, int>> q;
    q.push({0, s});

    while (!q.empty()) {
        // extract min
        int min = q.top().second;
        q.pop();
        if (visited[min]) continue;
        visited[min] = 1;
        if (min == e) break;

        // update distance
        list<pair<GraphNode *, int>> adj = graph->bucket[min]->adj;
        for (auto it = adj.begin(); it != adj.end(); it++) {
            if (d[min] + (*it).second < d[(*it).first->idx]) { // 여기에 !visited[(*it).first->idx] 추가해도 됨
                d[(*it).first->idx] = d[min] + (*it).second;
                q.push({-d[(*it).first->idx], (*it).first->idx});
                p[(*it).first->idx] = min;
            }
        }
    }

    // create path
    int tmp = e;
    while (tmp != s) {
        path_stack.push(tmp);
        tmp = p[tmp];
    }
    path_stack.push(s);

    int idx = 0;
    while (!path_stack.empty()) {
        dst[idx++] = path_stack.top();
        path_stack.pop();
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
        {INF, INF, INF, 4, 5, INF, 0}};

    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            graph->addEdge(i, j, weight[i][j]);
        }
    }

    vector<int> dst(MAX_SIZE);
    dijkstra(graph, 0, dst);

    for (int i = 0; i < MAX_SIZE; i++)
        cout << dst[i] << " ";
    cout << endl;

    // for (int i = 0; i < MAX_SIZE; i++) {
    //     vector<int> dst(MAX_SIZE, -1);
    //     dijkstra_path(graph, 0, i, dst);
    //     for (int j = 0; j < MAX_SIZE; j++) {
    //         if (dst[j] == -1) break;
    //         cout << dst[j] << " ";
    //     }
    //     cout << endl;
    // }

    delete graph;
}