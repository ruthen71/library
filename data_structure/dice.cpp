#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (int i = 0; i < (n); ++i)

struct dice {
    vector<ll> n;
    dice(vector<ll> n = {1, 2, 3, 5, 4, 6}) : n(n) {}
    ll num() { return n[0]; }
    void rotate_left() { rotate(n.begin() + 1, n.begin() + 2, n.end() - 1); }
    void rotate_right() { rep(i, 3) rotate_left(); }
    void rotate_north() {
        swap(n[0], n[2]);
        swap(n[2], n[5]);
        swap(n[5], n[4]);
    }
    void rotate_east() {
        swap(n[0], n[3]);
        swap(n[3], n[5]);
        swap(n[5], n[1]);
    }
    void rotate_south() { rep(i, 3) rotate_north(); }
    void rotate_west() { rep(i, 3) rotate_east(); }
};
