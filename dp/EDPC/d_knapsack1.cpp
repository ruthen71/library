// EDPC D - Knapsack1
// https://atcoder.jp/contests/dp/submissions/17532641
// AOJ DPL_1_B
// https://onlinejudge.u-aizu.ac.jp/status/users/ruthen71/submissions/1/DPL_1_B/judge/4927664/C++17

#include <iostream>
#include <vector>

using namespace std;

long long knapsack1(vector<pair<int, long long>> &GOODS, int W_MAX, int N) {
    vector<vector<long long>> DP(N+1,vector<long long>(W_MAX+1,0));
    for (int i = 0; i < N; i++) {
        int W_NOW = GOODS[i].first;
        long long V_NOW = GOODS[i].second;
        for (int j = 0; j <= W_MAX; j++) {
            if (j-W_NOW >= 0) {
                DP[i+1][j] = max(DP[i][j], DP[i][j-W_NOW]+V_NOW);
            } else {
                DP[i+1][j] = DP[i][j];
            }
        }
    }
    return DP[N][W_MAX];
}

int main() {
    int n,w; cin >> n >> w;
    vector<pair<int, long long>> goods(n);
    for (int i = 0; i < n; i++) cin >> goods[i].first >> goods[i].second;
    // AOJはこっち
    // for (int i = 0; i < n; i++) cin >> goods[i].second >> goods[i].first;
    long long res = knapsack1(goods, w, n);
    cout << res << endl;
    return 0;
}
