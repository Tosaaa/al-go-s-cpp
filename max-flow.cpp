// Max Flow (Ford-Fulkerson with BFS (Edmonds-Karp))
// TODO: 가중치 0인 간선을 아예 제거해버려야 더 빠를듯..

#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

#include "graph.hpp"

#define REP(i, a, b) for (int(i) = (a); (i) < (b); (i)++)
#define endl '\n'
#define MAX_SIZE 4

using namespace std;

void maxFlow(Graph *graph, int s, int t);
bool findPath(Graph *graph, int s, int t, vector<int> &path);

int maxFlow(Graph *graph, int s, int t) {
    if (s == t)
        cout << "source is equal to sink" << endl;
    else if (t >= graph->V)
        cout << "sink too large" << endl;

    int maxflow = 0;

    while (1) {
        vector<int> path(graph->getNodeSize(), -1);    

        if (!findPath(graph, s, t, path)) {
            //cout << "Max Flow Found!: " << maxflow << endl;
            break;
        } else {
            int len = 0;
            REP(i, 0, graph->getNodeSize()) {
                if (path[i] == -1) break;
                cout << path[i] << " ";
                len++;
            }
            //cout << endl;

            GraphNode *node;
            int min = INF;
            REP(i, 0, len) {
                node = graph->bucket[path[i]];
                for (auto it = node->adj.begin(); it != node->adj.end(); it++) {
                    if ((*it).first->idx == path[i+1] && (*it).second < min) {
                        min = (*it).second;
                    }
                }
            }
            maxflow += min;
            //cout << "incremented flow: " << min << ", current flow: " << maxflow << endl;
            //graph->print();

            REP(i, 0, len) {
                node = graph->bucket[path[i]];
                for (auto it = node->adj.begin(); it != node->adj.end(); it++) {
                    if ((*it).first->idx == path[i+1]) {
                        (*it).second -= min;
                    }
                }
            }
            
            //graph->print();

            for (int i = len-1; i > 0; i--) {
                bool isEdge = false;
                node = graph->bucket[path[i]];
                for (auto it = node->adj.begin(); it != node->adj.end(); it++) {
                    if ((*it).first->idx == path[i-1]) {
                        (*it).second += min;
                        isEdge = true;
                    }
                }
                if (!isEdge) graph->addEdge(path[i], path[i-1], min);
            }
            //graph->print();
        }
    }
    return maxflow;
}

bool findPath(Graph *graph, int s, int t, vector<int> &path) {
    vector<int> visited(graph->getNodeSize());
    queue<int> q;
    vector<int> p(graph->getNodeSize(), -1);
    stack<int> path_stack;

    visited[s] = 1;
    q.push(s);
    bool valid = false;

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (v == t) {
            valid = true;
            break;
        }

        list<pair<GraphNode *, int>> adj = graph->bucket[v]->adj;
        for (auto it = adj.begin(); it != adj.end(); it++) {
            if (!visited[(*it).first->idx] && (*it).second > 0) {
                q.push((*it).first->idx);
                visited[(*it).first->idx] = 1;
                p[(*it).first->idx] = v;
            }
        }
    }
    if (valid) {
        int tmp = t;
        while (tmp != s) {
            path_stack.push(tmp);
            tmp = p[tmp];
        }
        path_stack.push(s);

        int idx = 0;
        while (!path_stack.empty()) {
            path[idx++] = path_stack.top();
            path_stack.pop();
        }
        return true;
    }
    return false;
}

int main() {
    Graph *graph = new Graph(MAX_SIZE);

    // book example
    // int weight[MAX_SIZE][MAX_SIZE] = {
    //     {0, 5, INF, 4, INF, INF},
    //     {INF, 0, 6, INF, INF, INF},
    //     {INF, INF, 0, INF, 8, 5},
    //     {INF, 3, INF, 0, 1, INF},
    //     {INF, INF, INF, INF, 0, 2},
    //     {INF, INF, INF, INF, INF, 0}};

    // ratsgo's example
    int weight[MAX_SIZE][MAX_SIZE] = {
        {0, 2, 5, INF},
        {INF, 0, 1, 4},
        {INF, INF, 0, 3},
        {INF, INF, INF, 0}};

    // gazelle's example
    // int weight[MAX_SIZE][MAX_SIZE] = {
    //     {0, 7, INF, 5, INF, INF},
    //     {INF, 0, 3, 5, INF, INF},
    //     {INF, INF, 0, 2, INF, 6},
    //     {INF, INF, INF, 0, 9, INF},
    //     {INF, INF, 2, INF, 0, 4},
    //     {INF, INF, INF, INF, INF, 0}};

    REP(i, 0, MAX_SIZE) {
        REP(j, 0, MAX_SIZE) {
            graph->addEdge(i, j, weight[i][j]);
        }
    }

    cout << maxFlow(graph, 0, 3) << endl;

    delete graph;

    return 0;
}