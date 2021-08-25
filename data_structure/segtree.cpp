#include <bits/stdc++.h>
using namespace std;

template <class T>
struct segtree {
    int _n;
    vector<T> dat;
    segtree() {}
    segtree(int n) {
        _n = 1;
        while (_n < n) _n *= 2;
        dat = vector<T>(2 * _n - 1, 0);
    }
    void update(int k, T a) {
        k += _n - 1;
        dat[k] = a;
        while (k > 0) {
            k = (k - 1) / 2;
            dat[k] = max(dat[2 * k + 1], dat[2 * k + 2]);
        }
    }
    T query(int a, int b, int k = 0, int l = 0, int r = -1) {
        if (r == -1) r = _n;
        if (r <= a || b <= l) return 0;
        if (a <= l && r <= b) return dat[k];
        T vl = query(a, b, 2 * k + 1, l, (l + r) / 2);
        T vr = query(a, b, 2 * k + 2, (l + r) / 2, r);
        return max(vl, vr);
    }
};