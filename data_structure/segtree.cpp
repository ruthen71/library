#include <bits/stdc++.h>
using namespace std;

template <class T>
struct segtree {
    // ↓↓↓↓↓ change here! ↓↓↓↓↓
    T f(T a, T b) { return min(a, b); }
    T e() { return INT_MAX; }
    // ↑↑↑↑↑ change here! ↑↑↑↑↑
    int n, _n;
    vector<T> dat;
    segtree(int n) : n(n) {
        _n = 1;
        while (_n < n) _n *= 2;
        dat = vector<T>(2 * _n - 1, e());
    }
    void update(int k, T a) {
        k += _n - 1;
        dat[k] = a;
        while (k > 0) {
            k = (k - 1) / 2;
            dat[k] = f(dat[2 * k + 1], dat[2 * k + 2]);
        }
    }
    T query(int a, int b, int k, int l, int r) {
        if (r <= a || b <= l) return e();
        if (a <= l && r <= b) return dat[k];
        T vl = query(a, b, 2 * k + 1, l, (l + r) / 2);
        T vr = query(a, b, 2 * k + 2, (l + r) / 2, r);
        return f(vl, vr);
    }
    T query(int a, int b) { return query(a, b, 0, 0, _n); }
};
