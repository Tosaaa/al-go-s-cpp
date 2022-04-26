// Strongly Connected Components (Kosaraju's Algorithm)

#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

#include "graph.hpp"

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;

#define REP(i, a, b) for (int i = a; i < b; i++)
#define endl '\n'
#define MAX_SIZE 5

void DFS(Graph *graph, int v, vi &visited, stack<int> &s);
void DFS(Graph *graph, int v, vi &visited);

void kosaraju(Graph *graph) {
    int V = graph->getNodeSize();
    stack<int> s;
    vi visited(V);
    REP(i, 0, V) {
        if (!visited[i])
            DFS(graph, i, visited, s);
    }

    Graph *trans = new Graph(V);
    REP(i, 0, V) {
        for (auto it = graph->bucket[i]->adj.begin(); it != graph->bucket[i]->adj.end(); it++) {
            trans->addEdge((*it).first->idx, i, (*it).second);
        }
    }

    REP(i, 0, V) {
        visited[i] = 0;
    }

    while (!s.empty()) {
        if (!visited[s.top()]) {
            DFS(trans, s.top(), visited);
            cout << endl;
        }
        s.pop();
    }
    delete trans;
    return;
}

void DFS(Graph *graph, int v, vi &visited, stack<int> &s) {
    visited[v] = 1;

    for (auto it = graph->bucket[v]->adj.begin(); it != graph->bucket[v]->adj.end(); it++) {
        if (!visited[(*it).first->idx]) {
            DFS(graph, (*it).first->idx, visited, s);
        }
    }
    s.push(v);
    return;
}

void DFS(Graph *graph, int v, vi &visited) {
    visited[v] = 1;
    cout << v << " ";

    for (auto it = graph->bucket[v]->adj.begin(); it != graph->bucket[v]->adj.end(); it++) {
        if (!visited[(*it).first->idx]) {
            DFS(graph, (*it).first->idx, visited);
        }
    }
    return;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Graph *graph = new Graph(MAX_SIZE);
    int weight[MAX_SIZE][MAX_SIZE] = {
        {0, INF, 1, 1, INF},
        {1, 0, INF, INF, INF},
        {INF, 1, 0, INF, INF},
        {INF, INF, INF, 0, 1},
        {INF, INF, INF, INF, 0}};

    REP(i, 0, MAX_SIZE) {
        REP(j, 0, MAX_SIZE) {
            graph->addEdge(i, j, weight[i][j]);
        }
    }

    kosaraju(graph);

    delete graph;

    return 0;
}