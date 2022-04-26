// Topological Sort

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

#include "graph.hpp"

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;

#define REP(i, a, b) for (int i = a; i < b; i++)
#define endl '\n'
#define MAX_SIZE 7

vi topological_sort(Graph *graph) {
    int V = graph->getNodeSize();
    vi indegree(V, 0);
    REP(i, 0, V) {
        for (auto it = graph->bucket[i]->adj.begin(); it != graph->bucket[i]->adj.end(); it++) {
            indegree[(*it).first->idx]++;
        }
    }

    queue<int> q;
    REP(i, 0, V) {
        if (!indegree[i]) q.push(i);
        cout << indegree[i] << endl;
    }

    vi ret;
    REP(i, 0, V) {
        if (q.empty()) {
            cout << "Topological Sort Impossible";
            return vi();
        }
        int v = q.front();
        q.pop();
        ret.push_back(v);
        for (auto it = graph->bucket[v]->adj.begin(); it != graph->bucket[v]->adj.end(); it++) {
            indegree[(*it).first->idx]--;
            if (indegree[(*it).first->idx] == 0) q.push((*it).first->idx);
        }
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Graph *graph = new Graph(MAX_SIZE);

    int weight2[MAX_SIZE][MAX_SIZE] = {
        {0, 1, INF, INF, 1, INF, INF},
        {INF, 0, 1, INF, INF, 1, INF},
        {INF, INF, 0, 1, INF, INF, INF},
        {INF, INF, INF, 0, INF, INF, 1},
        {INF, INF, INF, INF, 0, 1, INF},
        {INF, INF, INF, 1, INF, 0, INF},
        {INF, INF, INF, INF, INF, INF, 0}};

    REP(i, 0, MAX_SIZE) {
        REP(j, 0, MAX_SIZE) {
            graph->addEdge(i, j, weight2[i][j]);
        }
    }

    graph->print();

    vi dst = topological_sort(graph);
    REP(i, 0, MAX_SIZE) {
        cout << dst[i] + 1 << " ";
    }
    cout << endl;

    return 0;
}