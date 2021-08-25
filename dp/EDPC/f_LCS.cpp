// EDPC F - LCS
// https://atcoder.jp/contests/dp/submissions/17533226

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int S_MAX = 10000;

string LCS(string &S, string &T) {
    int N = S.size(), M = T.size();
    vector<vector<int>> DP(N+1,vector<int>(M+1,0));
    vector<vector<int>> LAST(N+1,vector<int>(M+1,0));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (S[i] == T[j]) {
                DP[i+1][j+1] = DP[i][j]+1;
                LAST[i+1][j+1] = S_MAX*i+j;
            } else {
                if (DP[i+1][j] > DP[i][j+1]) {
                    DP[i+1][j+1] = DP[i+1][j];
                    LAST[i+1][j+1] = LAST[i+1][j];
                } else {
                    DP[i+1][j+1] = DP[i][j+1];
                    LAST[i+1][j+1] = LAST[i][j+1];
                }
            }
        }
    }
    string RES = "";
    int i = N, j = M;
    while (i && j) {
        int ii = LAST[i][j] / S_MAX, jj = LAST[i][j] % S_MAX;
        if (S[ii] == T[jj]) RES += S[ii];
        i = ii; j = jj;
    }
    reverse(RES.begin(), RES.end());
    return RES;
}


int main() {
    string s,t; cin >> s >> t;
    string res = LCS(s,t);
    cout << res << endl;
    return 0;
}
