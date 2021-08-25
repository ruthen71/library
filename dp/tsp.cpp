// 巡回セールスマン問題(O(N^2 2^N))
// verified
// ABC 180 E - Traveling Salesman among Aerial Cities
// https://atcoder.jp/contests/abc180/submissions/17489568

#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

vector<vector<ll>> tsp(vector<vector<ll>> &DIST, int N) {
    const ll INF = 1ll << 60;
    ll N2 = 1 << N;
    vector<vector<ll>> DP(N2, vector<ll>(N, INF));
    // TSP:閉路なので始点をどこにしても良い
    // 始点を0とすると、「まだどこにも行ってないけど0にいる」ので
    DP[0][0] = 0;
    // TSP = 巡回セールスマン問題 = 最短ハミルトン「閉路」問題
    // 最短ハミルトン「路」問題の場合
    // 始点がiのとき -> DP[1<<i][i] = 0
    // DP[0][i]だと、「まだどこにも行ってないけど今iにいる」
    // DP[1<<i][i]だと、「iは既に訪問済みで、今iにいる」
    // 始点が任意の場合はrep(i,N) DP[1<<i][i] = 0;
    for (ll s = 0; s < N2; s++) {
        for (ll v = 0; v < N; v++) {
            if ((s & (1 << v)) != 0) continue;  // v in s
            for (ll u = 0; u < N; u++) {
                if (v != u) {
                    DP[s | (1 << v)][v] = min(DP[s | (1 << v)][v], DP[s][u] + DIST[u][v]);
                }
            }
        }
    }
    // なおDP[(1<<N)-1][0]のように()を付ける必要がある
    return DP;
}

int main() {
    int n; cin >> n;

    pair<pair<ll, ll>, ll> axis[n];
    for (int i = 0; i < n; i++) {
        ll x,y,z; cin >> x >> y >> z;
        axis[i] = {{x,y}, z};
    }

    vector<vector<ll>> dist(n, vector<ll>(n));
    for (int i = 0; i < n; i++) {
        ll a = axis[i].first.first, b = axis[i].first.second, c = axis[i].second;
        for (int j = 0; j < n; j++) {
            if (i == j) {
                dist[i][j] = 0;
                continue;
            }
            ll p = axis[j].first.first, q = axis[j].first.second, r = axis[j].second;
            dist[i][j] = abs(p-a)+abs(q-b)+max((ll)0,r-c);
        }
    }
    vector<vector<ll>> dp = tsp(dist, n);
    
    cout << dp[(1<<n)-1][0] << endl;

    return 0;
}
