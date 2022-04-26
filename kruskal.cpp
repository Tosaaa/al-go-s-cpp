// Kruskal's Algorithm (based on adjacency list)

#include <algorithm>
#include <iostream>
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

class UnionFind {
    public:
        vector<pii> root; //root[i][0]은 root, root[i][1]은 height(rank)
    UnionFind(int n) {
        REP(i, 0, n) {
            root.push_back({i, 0});
        }
    }
    int find(int x) {
        if (root[x].first == x) return x;
        return (root[x].first = find(root[x].first)); // Path Compression
    }
    void unite(int x, int y) {
        x = find(x);
        y = find(y);

        if (x == y) return;

        // Union-by-Height
        if (root[x].second > root[y].second) {
            root[y].first = x;
        } else if (root[x].second < root[y].second) {
            root[x].first = y;
        } else {
            root[y].first = x;
            root[x].second++;
        }
    }
    bool isSame(int x, int y) {
        return find(x) == find(y);
    }
};

Graph *kruskal(Graph *graph) {
    int V = graph->getNodeSize();
    int E = (graph->E) / 2;
    vector<tuple<int, int, int>> edges;
    REP(i, 0, V) {
        for (auto it = graph->bucket[i]->adj.begin(); it != graph->bucket[i]->adj.end(); it++) {
            int next = (*it).first->idx;
            if (i < next) {
                edges.push_back({(*it).second, i, next});
            }
        }
    }
    sort(edges.begin(), edges.end());

    Graph *ret = new Graph(V);
    UnionFind *uf = new UnionFind(V);
    REP(i, 0, E) {
        int w, u, v;
        tie(w, u, v) = edges[i];
        if (!uf->isSame(u, v)) {
            uf->unite(u, v);
            ret->addEdge(u, v, w);
            ret->addEdge(v, u, w);
        }
    }

    delete uf;
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

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

    Graph *mst = kruskal(graph);
    mst->print();

    delete graph;

    return 0;
}