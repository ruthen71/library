// UnionFind
// verified
// AOJ DSL_1_A Disjoint Set: Union Find Tree
// https://onlinejudge.u-aizu.ac.jp/status/users/ruthen71/submissions/1/DSL_1_A/judge/4990600/C++17


#include <iostream>
#include <vector>

using namespace std;

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
    int n, q; cin >> n >> q;
    UnionFind uf(n);
    while (q--) {
        int com, x, y; cin >> com >> x >> y;
        if (com == 0) uf.merge(x, y);
        else cout << uf.same(x, y) << '\n';
    }
    return 0;
}
