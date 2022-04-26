// Union-Find

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;

#define REP(i, a, b) for (int i = a; i < b; i++)
#define endl '\n'

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

// int main() {
//     ios_base::sync_with_stdio(0);
//     cin.tie(0);
//     cout.tie(0);

//     UnionFind *uf = new UnionFind(8);
//     uf->unite(0, 1);
//     uf->unite(3, 4);
//     uf->unite(5, 0);
//     uf->unite(2, 6);
//     uf->unite(6, 7);
//     uf->unite(1, 4);
//     REP(i, 0, 8) {
//         cout << uf->root[i].first<< " ";
//     }
//     cout << endl;

//     delete uf;

//     return 0;
// }