// max flow
// verified: https://onlinejudge.u-aizu.ac.jp/problems/GRL_6_A


#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define rep(i, n) for (ll i = 0; i < (n); i++)
#define sz(x) ((int)(x).size())
#define pb push_back
const ll INF = 1ll << 60;

struct edge {
    int to;
    ll cap;
    int rev;
};

void add_edge(int from, int to, ll cap, vector<vector<edge>> &g) {
    g[from].push_back((edge){to, cap, g[to].size()});
    g[to].push_back((edge){from, 0, g[from].size()-1});
    return;
}

ll dfs(int v, int t, ll f, vector<bool> &used, vector<vector<edge>> &g) {
    if (v == t) return f;
    used[v] = true;
    for (auto &e : g[v]) {
        if (!used[e.to] && e.cap > 0) {
            ll d = dfs(e.to, t, min(f, e.cap), used, g);
            if (d > 0) {
                e.cap -= d;
                g[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

ll max_flow(int s, int t, vector<vector<edge>> g) {
    // gを参照渡しにしたいときには&gにする
    ll flow = 0, n = sz(g);
    while (1) {
        vector<bool> used(n, 0);
        ll f = dfs(s, t, INF, used, g);
        if (f == 0) return flow;
        flow += f;
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<edge>> g(n);
    rep(i, m) {
        int v, u, c;
        cin >> v >> u >> c;
        // v -> u に コスト c
        g[v].pb({u, c, sz(g[u])});
        g[u].pb({v, 0, sz(g[v]) - 1});
    }
    ll ans = max_flow(0, n - 1, g);
    cout << ans << endl;
    return 0;
}
