#include <iostream>
#include <tuple>
#include <vector>

#include "graph.hpp"

using namespace std;

#define REP(i, a, b) for (int(i) = (a); (i) < (b); (i)++)
#define MAX_SIZE 7

void shortest_distance(Graph *graph, int s, vector<int> &dst) {
    int V = graph->getNodeSize();
    int E = graph->getEdgeSize(true);
    vector<int> d(V, INF);  // storing distances
    d[s] = 0;
    vector<tuple<int, int, int>> edges;
    for (auto it1 = graph->bucket.begin(); it1 != graph->bucket.end(); it1++) {
        for (auto it2 = (*it1)->adj.begin(); it2 != (*it1)->adj.end(); it2++) {
            edges.push_back({(*it1)->idx, (*it2).first->idx, (*it2).second});
        }
    }

    REP(i, 0, V - 1) {  // repeat v-1 times
        REP(j, 0, E) {
            int a, b, w;
            tie(a, b, w) = edges[j];
            if (d[a] < INF && d[b] > d[a] + w) {
                d[b] = d[a] + w;
            }
        }
    }

    int valid = 1;
    REP(j, 0, E) {
        int a, b, w;
        tie(a, b, w) = edges[j];
        if (d[a] < INF && d[b] > d[a] + w) {
            valid = 0;
            break;
        }
    }

    if (!valid) {
        cout << "Bellman-Ford impossible: negative cycle detected.\n"
             << endl;
        REP(i, 0, V) {
            dst[i] = -1;
        }
    } else {
        REP(i, 0, V) {
            dst[i] = d[i];
        }
    }
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

    // int weight2[MAX_SIZE][MAX_SIZE] = {
    //     {0, 20, INF},
    //     {INF, 0, -15},
    //     {INF, INF, 0}
    // };

    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            graph->addEdge(i, j, weight[i][j]);
        }
    }

    vector<int> dst(MAX_SIZE);
    shortest_distance(graph, 0, dst);

    REP(i, 0, MAX_SIZE) {
        cout << dst[i] << " ";
    }
    cout << endl;

    delete graph;

    return 0;
}