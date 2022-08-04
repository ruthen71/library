// 区間加算区間和
// https://atcoder.jp/contests/abc253/submissions/32061961

#include <bits/stdc++.h>

#include <atcoder/lazysegtree>

// 区間更新区間和
namespace RURSQ {
struct S {
    long long value;
    int size;
};
using F = long long;
const F ID = std::numeric_limits<F>::max();  // biginteger
S op(S a, S b) { return {a.value + b.value, a.size + b.size}; }
S e() { return {0, 0}; }  // used when prod(l, l) is called
S mapping(F f, S x) {
    if (f != ID) x.value = f * x.size;
    return x;
}
F composition(F f, F g) { return (f == ID ? g : f); }  // f(g(S))
F id() { return ID; }
};  // namespace RURSQ
// 使用例
// https://codeforces.com/contest/1690/submission/166925103
void RURSQ() {
    int N = 10;
    std::vector<RURSQ::S> v(N, {0, 1});  // value = 0, size = 1
    atcoder::lazy_segtree<RURSQ::S, RURSQ::op, RURSQ::e, RURSQ::F, RURSQ::mapping, RURSQ::composition, RURSQ::id> seg(v);
    // update
    // seg[3] = 15;
    seg.apply(3, 15);
    seg.set(3, {15, 1});  // {value, size}
    // seg[3] = seg[4] = seg[5] = 15;
    seg.apply(3, 6, 15);
    // sum
    // seg[3] + seg[4] + seg[5];
    seg.prod(3, 6).value;
    // seg[3]
    seg.get(3).value;
    return;
}
