#include <bits/stdc++.h>
using namespace std;

// \sum_{i=1}^{N} floor(N/i)
// O(sqrt(N))
// https://atcoder.jp/contests/abc230/submissions/27686117
long long fraction_floor_sum(long long N) {
    long long ret = 0, cur = 0;
    for (long long i = 1; i * i <= N; i++) {
        ret += N / i;
        cur = i;
    }
    for (long long i = cur; i >= 1; i--) {
        ret += i * (N / i - cur);
        cur = N / i;
    }
    return ret;
}

// clamp(x,a,b,c) = min(c, max(b, x+a))
// composite できる
// https://atcoder.jp/contests/abc196/submissions/27800646
struct myclamp {
    long long a, b, c;  // -10^9 <= a,b,c <= 10^9
    myclamp(long long a = 0, long long b = -numeric_limits<long long>::max() / 4, long long c = numeric_limits<long long>::max() / 4) : a(a), b(b), c(c) {}
    long long eval(long long x) {
        // -10^9 <= x <= 10^9
        return min(c, max(b, x + a));
    }
    myclamp compo(myclamp g) {
        // return g(f(x))
        return myclamp(this->a + g.a, max(g.b, this->b + g.a), min(g.c, max(g.b, this->c + g.a)));
    }
    myclamp compomax(long long d) {
        // return max(f(x), d)
        return compo(myclamp(0, d, numeric_limits<long long>::max() / 4));
    }
    myclamp compomin(long long d) {
        // return min(f(x), d)
        return compo(myclamp(0, -numeric_limits<long long>::max() / 4, d));
    }
    myclamp compoconst(long long d) {
        // return f(x) + d
        return compo(myclamp(d, -numeric_limits<long long>::max() / 4, numeric_limits<long long>::max() / 4));
    }
};