// EDPC E - Knapsack2
// https://atcoder.jp/contests/dp/submissions/17532853

#include <iostream>
#include <vector>

using namespace std;

const int V_MAX = 100005; // max{v_i}*n
const long long INFL = 1001001001001001000;


long long knapsack2(vector<pair<long long, int>> &GOODS, long long W, int N) {
    vector<vector<long long>> DP(N+1,vector<long long>(V_MAX+1,INFL));
    DP[0][0] = 0;
    for (int i = 0; i < N; i++) {
        long long W_NOW = GOODS[i].first;
        int V_NOW = GOODS[i].second;
        for (int j = 0; j <= V_MAX; j++) {
            if (j-V_NOW >= 0) {
                DP[i+1][j] = min(DP[i][j], DP[i][j-V_NOW]+W_NOW);
            } else {
                DP[i+1][j] = DP[i][j];
            }
        }
    }
    
    for (int j = V_MAX; j >= 0; j--) {
        if (DP[N][j] <= W) return j;
    }
    return 0ll;
}

int main() {
    int n; long long w; cin >> n >> w;
    vector<pair<long long, int>> goods(n);
    for (int i = 0; i < n; i++) cin >> goods[i].first >> goods[i].second;
    long long res = knapsack2(goods, w, n);
    cout << res << endl;
    return 0;
}
