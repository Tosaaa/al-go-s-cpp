// Boyer-Moore Algorithm
// cannot understand how to implement!!
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#define REP(i, a, b) for (int(i) = (a); (i) < (b); (i)++)
#define endl '\n'

using namespace std;

int skip(string str, char c) {
    int N = str.size();
    REP(i, 0, N) { // search backward
        if (str[N-i-1] == c)
            return i;
    }
    return N;
}

vector<int> boyer_moore(string str, string pattern) {
    // vector<int> ans;
    // int N = str.size();
    // int M = pattern.size();
    
    // REP(i, M-1, N) {
    //     if (str[i] == str[M-1]) {
    //         REP(j, 1, M) {
    //             if (str[i-j] != str[M-1-j]) {
    //                 i += skip(pattern, str[i-j]) - j; // HOW?
    //                 break;
    //             }
    //         }
    //     } else {
    //         i += skip(pattern, str[i]);
    //     }
    // }

    
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string str, pattern;
    getline(cin, str);
    getline(cin, pattern);

    vector<int> ans = boyer_moore(str, pattern);
    REP(i, 0, ans.size()) {
        cout << ans[i] << " ";
    }
    cout << endl;

    return 0;
}