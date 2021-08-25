// 最小共通祖先(Lowest Common Ancestor)
// verified
// AOJ GRL_5_C LCA: Lowest Common Ancestor
// https://onlinejudge.u-aizu.ac.jp/status/users/ruthen71/submissions/1/GRL_5_C/judge/5199828/C++14


#include <bits/stdc++.h>
using namespace std;


using ll = long long;
#define rep(i,n) for (ll i = 0; i < (n); i++)
#define pb push_back

const int N = 100005;
ll depth[N], parent[N];
ll dbl[35][N];
vector<ll> g[N];
// depthとparentを計算
void dfs(ll par, ll cur) {
    if (par == -1) depth[cur] = 0;
    else depth[cur] = depth[par]+1;
    parent[cur] = par;
    for (ll nx : g[cur]) {
        if (nx == par) continue;
        dfs(cur, nx);
    }
}
// LCAを計算
ll lca(ll u, ll v) {
    if (depth[u] > depth[v]) swap(u, v);    // uの方が浅い
    rep(i,30) {
        if ((depth[v]-depth[u])>>i&1) v = dbl[i][v];
    }
    if (u == v) return u;
    // 同じ深さになった
    for (int i = 29; i >= 0; i--) {
        if (dbl[i][u] != dbl[i][v]) {
            u = dbl[i][u];
            v = dbl[i][v];
        }
    }
    return dbl[0][u];
}

int main() {
    // 入力
    ll n; cin >> n;
    rep(i,n) {
        ll k; cin >> k;
        rep(j,k) {
            ll c; cin >> c;
            g[i].pb(c);
            g[c].pb(i);
        }
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
        ll root = lca(a, b);
        cout << root << '\n';
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


