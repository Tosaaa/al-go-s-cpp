// Prim's Algorithm (based on adjacenty list)

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#include <tuple>

#include "graph.hpp"

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;

#define REP(i, a, b) for (int i = a; i < b; i++)
#define endl '\n'
#define MAX_SIZE 7

Graph *prim(Graph *graph) {
    int V = graph->getNodeSize();
    vi visited(V);
    vi d(V, INF);
    priority_queue<tuple<int, int, int>> pq;
    pq.push({0, 0, 0});

    Graph *ret = new Graph(V);
    while (!pq.empty()) {
        int val, u, v;
        tie(val, u, v) = pq.top();
        val = -val;
        
        pq.pop();
        if (visited[v]) continue;
        visited[v] = 1;
        //cout << val << " " << u << " " << v << endl;
        if (u != v) {
            ret->addEdge(u, v, val);
            ret->addEdge(v, u, val);
        }

        for (auto it = graph->bucket[v]->adj.begin(); it != graph->bucket[v]->adj.end(); it++) {
            int next = (*it).first->idx;
            int weight = (*it).second;
            if (d[next] > weight) {
                d[next] = weight;
                pq.push({-weight, v, next});
            }
        }
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    Graph *graph = new 
    Graph(MAX_SIZE);
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

    Graph *mst = prim(graph);
    mst->print();
    return 0;
}