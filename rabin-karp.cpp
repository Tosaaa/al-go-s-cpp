// Rabin-Karp Algorithm
// TODO: overflow? => 무시할 수 있다는 듯

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#define REP(i, a, b) for (int(i) = (a); (i) < (b); (i)++)
#define endl '\n'

using namespace std;

vector<int> rabin_karp(string str, string pattern) {
    vector<int> ans;
    int N = str.size();
    int M = pattern.size();
    int hash_pattern = 0;
    int hash_str = 0;
    REP(i, 0, M) {
        hash_str += str[i] * pow(2, M - i - 1);
        hash_pattern += pattern[i] * pow(2, M - i - 1);
    }

    int valid = 0;
    REP(i, 0, N - M + 1) {
        //cout << hash_str << " " << hash_pattern << endl;
        if (hash_pattern == hash_str) {
            //cout << "same" << endl;
            valid = 1;
            REP(j, 0, M) {
                if (str[i + j] != pattern[j]) {
                    valid = 0;
                    break;
                }
            }
            if (valid) {
                //cout << "valid" << endl;
                ans.push_back(i);
            }
        }
        if (i == N - M) break;
        hash_str -= str[i] * pow(2, M - 1);
        hash_str *= 2;
        hash_str += str[i + M];
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string str, pattern;
    getline(cin, str);
    getline(cin, pattern);

    vector<int> ans = rabin_karp(str, pattern);
    REP(i, 0, ans.size()) {
        cout << ans[i] << " ";
    }
    cout << endl;

    return 0;
}