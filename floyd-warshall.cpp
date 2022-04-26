#include <iostream>
#include <tuple>
#include <vector>

#include "graph.hpp"

using namespace std;

#define REP(i, a, b) for (int(i) = (a); (i) < (b); (i)++)
#define MAX_SIZE 7

void shortest_distance(Graph *graph, int s, vector<vector<int>> &dst) {
    int V = graph->getNodeSize();
    for (auto it1 = graph->bucket.begin(); it1 != graph->bucket.end(); it1++) {
        for (auto it2 = (*it1)->adj.begin(); it2 != (*it1)->adj.end(); it2++) {
             dst[(*it1)->idx][(*it2).first->idx] = (*it2).second;  
        }
    }

    REP(i, 0, V) {
        REP(j, 0, V) {
            if (dst[i][j] == 0 && i != j)
                dst[i][j] = INF;
        }
    }

    int valid = 1;
    for (int k = 0; k < V && valid == 1; k++) {
        for (int i = 0; i < V && valid == 1; i++) {
            for (int j = 0; j < V && valid == 1; j++) {
                if (dst[i][k] < INF && dst[k][j] < INF && dst[i][j] > dst[i][k] + dst[k][j])
                    dst[i][j] = dst[i][k] + dst[k][j];
                if (i == j && dst[i][j] < 0) valid = 0;
            }
        }
    }

    if (!valid)
        cout << "Floyd-Warshall impossible: negative cycle detected." << endl;
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

    vector<vector<int>> dst(MAX_SIZE, vector<int>(MAX_SIZE, 0));
    shortest_distance(graph, 0, dst);

    REP(i, 0, MAX_SIZE) {
        REP(j, 0, MAX_SIZE) {
            if (dst[i][j] == INF)
                cout << "- ";
            else
                cout << dst[i][j] << " ";
        }
        cout << endl;
    }

    delete graph;

    return 0;
}