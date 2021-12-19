#include <bits/stdc++.h>
using namespace std;

// slope trick
// ref:https://maspypy.com/slope-trick-1-%e8%a7%a3%e8%aa%ac%e7%b7%a8
// ref:https://ei1333.github.io/library/structure/others/slope-trick.cpp
// 累積min, 逆向き累積min, スライド最小値関数, +aだけ平行移動 はバグってる可能性あり
// うしさんのライブラリと比べると、累積minや逆向き累積minが早い(かもしれない)
// ABC127-Fを殴れる

template <class T>
struct slope_trick {
    const T INF = numeric_limits<T>::max() / 4;
    T min_f, add_l, add_r;  // push時に引く, top時に足す
    priority_queue<T, vector<T>, less<T>> L;
    priority_queue<T, vector<T>, greater<T>> R;
    slope_trick() : min_f(T(0)), add_l(T(0)), add_r(T(0)) {
        L.push(-INF);
        R.push(INF);
    }
    // return min{f(x)}
    T get_min_f() { return min_f; }
    // return argmin{f(x)}
    pair<T, T> get_argmin_f() { return make_pair(L.top() + add_l, R.top() + add_r); }
    // f(x) += a
    void add_const(const T &a) { min_f += a; }
    // f(x) += max(x-a, 0)
    void add_x_a(const T &a) {
        min_f += max(T(0), (L.top() + add_l) - a);
        L.push(a - add_l);
        T tmp = L.top() + add_l;
        L.pop();
        R.push(tmp - add_r);
    }
    // f(x) += max(a-x, 0)
    void add_a_x(const T &a) {
        min_f += max(T(0), a - (R.top() + add_r));
        R.push(a - add_r);
        T tmp = R.top() + add_r;
        R.pop();
        L.push(tmp - add_l);
    }
    // f(x) += abs(x-a)
    void add_abs(const T &a) {
        add_x_a(a);
        add_a_x(a);
    }
    // 累積min (not verified)
    void clear_R() {
        priority_queue<T, vector<T>, greater<T>>().swap(R);
        R.push(INF);
    }
    // 逆向き累積min (not verified)
    void clear_L() {
        priority_queue<T, vector<T>, less<T>>().swap(L);
        L.push(-INF);
    }
    // スライド最小値関数 g(x) = min(f(y)) (x-b<=y<=x-a)
    // (not verified)
    void ch_slide_min(const T &a, const T &b) {
        assert(a <= b);
        add_l += a;
        add_r += b;
    }
    // +aだけ平行移動 g(x) = f(x-a)
    // (not verified)
    void shift(const T &a) { ch_slide_min(a, a); }
};
