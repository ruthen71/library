#include <bits/stdc++.h>

#include <atcoder/segtree>

// 1点更新区間最小値
namespace RmQ {
using S = long long;
S op(S a, S b) { return std::min(a, b); }
S e() { return std::numeric_limits<S>::max(); }
};  // namespace RmQ
// https://codeforces.com/contest/1690/submission/166925103
void RmQ() {
    int N = 10;
    atcoder::segtree<RmQ::S, RmQ::op, RmQ::e> seg(N);
    // update
    // seg[3] = 15;
    seg.set(3, 15);
    // min
    // min(seg[3], seg[4], seg[5]);
    seg.prod(3, 6);
    // seg[3]
    seg.get(3);
    return;
}
