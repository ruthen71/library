// クラスカル法
// verified
// AOJ GRL_2_A Minimum Spanning Tree 
// https://onlinejudge.u-aizu.ac.jp/status/users/ruthen71/submissions/1/GRL_2_A/judge/5129293/C++14


#include <bits/stdc++.h>
using namespace std;

using ll = long long int;
using P = pair<ll, ll>;
#define rep(i,n) for (int i = 0; i < (n); i++)
#define all(v) (v).begin(), (v).end()


struct UnionFind {
    vector<int> parents;

    UnionFind() {}
    UnionFind(int n) : parents(n, -1) {}

    int leader(int x) {
        if (parents[x] < 0) return x;
        else return parents[x] = leader(parents[x]);
    }
    bool merge(int x, int y) {
        x = leader(x);
        y = leader(y);
        if (x == y) return false;
        if (parents[x] > parents[y]) swap(x, y);
        parents[x] += parents[y];
        parents[y] = x;
        return true;
    }
    bool same(int x, int y) { return leader(x) == leader(y); }
    int size(int x) { return -parents[leader(x)]; }
    void init(int n) { parents.assign(n, -1);}      // reset
};

int main() {
    int V, E; cin >> V >> E;
    vector<pair<int, P>> es(E);
    rep(i,E) cin >> es[i].second.first >> es[i].second.second >> es[i].first;
    sort(all(es));
    UnionFind uf(V);
    ll ans = 0;
    rep(i,E) {
        if (!uf.same(es[i].second.first, es[i].second.second)) {
            uf.merge(es[i].second.first, es[i].second.second);
            ans += es[i].first;
        }
    }
    cout << ans << endl;
    return 0;
}