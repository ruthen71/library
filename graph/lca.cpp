// 最小共通祖先(Lowest Common Ancestor)
// verified
// AOJ GRL_5_C LCA: Lowest Common Ancestor
// https://onlinejudge.u-aizu.ac.jp/status/users/ruthen71/submissions/1/GRL_5_C/judge/5199828/C++14
// ↓new!↓
// https://onlinejudge.u-aizu.ac.jp/status/users/ruthen71/submissions/1/GRL_5_C/judge/6150132/C++14

#include <bits/stdc++.h>
using namespace std;

struct lowest_common_ancestor {
    vector<vector<int>> G;
    vector<int> depth;
    vector<vector<int>> parent;
    int n, LOG;  // n = 頂点数, root = 根とする頂点番号, LOG = ダブリングする深さ
    lowest_common_ancestor(int n) : n(n), LOG(32 - __builtin_clz(n)), G(n) {}
    void add_edge(int u, int v) {
        // 無向辺{u, v}を加える
        G[u].push_back(v);
        G[v].push_back(u);
    }
    void build(int root = 0) {
        depth.assign(n, 0);
        parent.assign(LOG, vector<int>(n, 0));
        dfs(root, -1, 0);
        for (int k = 0; k + 1 < LOG; k++) {
            for (int v = 0; v < n; v++) {
                if (parent[k][v] < 0)
                    parent[k + 1][v] = -1;
                else
                    parent[k + 1][v] = parent[k][parent[k][v]];
            }
        }
    }
    void dfs(int cur, int par, int d) {
        parent[0][cur] = par;
        depth[cur] = d;
        for (auto &nx : G[cur]) {
            if (nx != par) dfs(nx, cur, d + 1);
        }
    }
    int lca(int u, int v) {
        assert((int)depth.size() == n);
        if (depth[u] > depth[v]) swap(u, v);
        // depth[u] <= depth[v](vの方が深い)
        // 同じ深さまでvが登る
        for (int k = 0; k < LOG; k++) {
            if ((depth[v] - depth[u]) >> k & 1) {
                v = parent[k][v];
            }
        }
        if (u == v) return u;
        for (int k = LOG - 1; k >= 0; k--) {
            if (parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return parent[0][u];
    }
};

int main() {
    int n;
    cin >> n;
    lowest_common_ancestor Lca(n);
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int c;
            cin >> c;
            if (i < c) Lca.add_edge(i, c);
        }
    }
    Lca.build();
    int Q;
    cin >> Q;
    while (Q--) {
        int u, v;
        cin >> u >> v;
        cout << Lca.lca(u, v) << '\n';
    }
    return 0;
}

/*
// ABC014 D
int main() {
    // 入力
    ll n; cin >> n;
    rep(i,n-1) {
        ll a, b; cin >> a >> b;
        a--; b--;
        g[a].pb(b);
        g[b].pb(a);
    }
    // 親と深さを求める
    dfs(-1, 0);
    // ダブリング前計算
    rep(i,n) dbl[0][i] = parent[i];
    rep(i,29) {
        rep(j,n) {
            if (dbl[i][j] == -1) dbl[i+1][j] = -1;
            else dbl[i+1][j] = dbl[i][dbl[i][j]];
        }
    }
    ll q; cin >> q;
    while (q--) {
        ll a, b; cin >> a >> b;
        a--; b--;
        ll root = lca(a, b);
        ll ans = depth[a]+depth[b]+1-2*depth[root];
        cout << ans << '\n';
    }
    return 0;
}
*/
