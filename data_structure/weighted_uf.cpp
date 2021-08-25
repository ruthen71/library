// 重み付きUnionFind
// verified
// AOJ DSL_1_B 重み付きUnion Find木
// https://onlinejudge.u-aizu.ac.jp/status/users/ruthen71/submissions/1/DSL_1_B/judge/5199152/C++14

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i,n) for (ll i = 0; i < (n); i++)

template <class T>
struct WeightedUnionFind {
    vector<int> parents;
    vector<T> diff_weight;

    WeightedUnionFind() {}
    WeightedUnionFind(int n) : parents(n, -1), diff_weight(n) {}

    int leader(int x) {
        if (parents[x] < 0) return x;
        else {
            int r = leader(parents[x]);
            diff_weight[x] += diff_weight[parents[x]];
            return parents[x] = r;
        }
    }
    T weight(int x) {
        leader(x);
        return diff_weight[x];
    }
    // weight(y) = weight(x) + w となるようにmerge
    bool merge(int x, int y, T w) {
        w += weight(x);
        w -= weight(y);
        x = leader(x), y = leader(y);
        if (x == y) return false;
        if (parents[x] > parents[y]) swap(x, y), w = -w;
        parents[x] += parents[y];
        parents[y] = x;
        diff_weight[y] = w;
        return true;
    }
    T diff(int x, int y) { return weight(y) - weight(x); }
    bool same(int x, int y) { return leader(x) == leader(y); }
    int size(int x) { return -parents[leader(x)]; }
    void init(int n) { parents.assign(n, -1), diff_weight.assign(n, 0);}      // reset
};

int main() {
    int n, q; cin >> n >> q;
    WeightedUnionFind<ll> uf(n);
    while (q--) {
        int type; cin >> type;
        if (type == 0) {
            ll x, y, z; cin >> x >> y >> z;

            uf.merge(x, y, z);
        } else {
            ll x, y; cin >> x >> y;
            if (uf.same(x, y)) cout << uf.diff(x, y) << '\n';
            else puts("?");
        }
    }
    return 0;
}


/*
// https://atcoder.jp/contests/abc087/submissions/19932799
// ABC 087 D - People on a Line
int main() {
    int N, M; cin >> N >> M;
    WeightedUnionFind<ll> uf(N);
    rep(i,M) {
        ll L, R, D; cin >> L >> R >> D;
        L--; R--;
        if (uf.same(L, R)) {
            if (uf.diff(L, R) != D) {
                puts("No");
                return 0;
            }
        } else uf.merge(L, R, D);
    }
    puts("Yes");
    return 0;
}
*/


