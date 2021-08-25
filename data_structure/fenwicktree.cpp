// Fenwick Tree
// verified
// AOJ DSL_2_B Range Sum Query (RSQ)
// https://onlinejudge.u-aizu.ac.jp/status/users/ruthen71/submissions/1/DSL_2_B/judge/5104750/C++14
// 内部では1-indexedで外部からは0-indexedになっている


#include <bits/stdc++.h>

using namespace std;

template <class T>
struct fenwick_tree {
    int N;
    vector<T> seg;
    fenwick_tree(int N) : N(N), seg(N+1, 0) {}

    // i番目の要素にxを加算する
    void add(int i, T x) {
        i++;    // 1-indexedにする
        while (i <= N) {
            seg[i] += x;
            i += i & -i;
        }
    }

    // 区間[0, i)の和!!
    // iを含まないことに注意!!
    T sum(int i) {
        T s = 0;
        while (i > 0) {
            s += seg[i];
            i -= i & -i;
        }
        return s;
    }

    // 区間[a, b)の和
    T sum(int a, int b) {
        return sum(b) - sum(a);
    }
};


int main() {
    int n, q; cin >> n >> q;
    fenwick_tree<int> fen(n);
    while (q--) {
        int com; cin >> com;
        if (com == 0) {
            int i, x; cin >> i >> x;
            i--;
            fen.add(i, x);
        } else {
            int x, y; cin >> x >> y;
            x--; y--;
            cout << fen.sum(x, y+1) << '\n';
        }
    }
    return 0;
}
