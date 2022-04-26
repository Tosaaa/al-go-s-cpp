// KMP (Knuth-Morris-Pratt) Algorithm

#include <iostream>
#include <vector>

#define REP(i, a, b) for (int (i) = (a); (i) < (b); (i)++)
#define endl '\n'

using namespace std;


vector<int> makeFail(string pattern) {
    int N = pattern.size();
    vector<int> fail(N, 0);
    int j = 0;
    REP(i, 1, N) {
        while (j > 0 && pattern[j] != pattern[i]) {
            j = fail[j-1];
        }
        if (pattern[j] == pattern[i]) {
            fail[i] = ++j;
        }
    }
    return fail;
}

vector<int> KMP(string s, string pattern) {
    vector<int> ans;
    vector<int> fail = makeFail(pattern);
    int n = s.size(), m = pattern.size();
    int j = 0;
    REP(i, 0, n) {
        while (j > 0 && pattern[j] != s[i]) {
            j = fail[j-1];
        }
        if (pattern[j] == s[i]) {
            if (j == m-1) {
                ans.push_back(i-m+1);
                j = fail[j];
            } else {
                j++;
            }
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s = "abcdabcdabee";
    string pattern = "abcdabe";

    vector<int> ans = KMP(s, pattern);

    REP(i, 0, ans.size()) {
        cout << ans[i] << " ";
    }
    cout << endl;

    return 0;
}
