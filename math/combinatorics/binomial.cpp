#include <bits/stdc++.h>
using namespace std;

// O(KlogK)
template <class Mint> Mint binomial(long long N, long long K) {
    if (N < 0 || K < 0 || N < K) return 0;
    Mint ret1 = 1, ret2 = 1;
    K = min(K, N - K);
    for (long long i = 1; i <= K; i++) {
        ret1 *= N--;
        ret2 *= i;
    }
    return ret1 / ret2;
}

/**
 * 使い方
 * mint ans = binomial(N, K, mint(0));
 * Tは型指定用(この使い方は良くない気がするけど解決策がわからない)->template で解決
 * https://atcoder.jp/contests/abc205/submissions/27460765 (ABC205-E)
 */
