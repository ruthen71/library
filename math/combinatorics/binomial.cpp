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

// 前計算O(N), クエリO(1)
// problem : https://atcoder.jp/contests/abc171/submissions/31917283
template <class Mint> struct binomials {
    vector<Mint> facl, facl_inv;
    binomials(int N) {
        facl.resize(N + 1);
        facl[0] = 1;
        for (int i = 1; i <= N; i++) facl[i] = facl[i - 1] * i;
        facl_inv.resize(N + 1);
        facl_inv[N] = 1 / facl[N];
        for (int i = N - 1; i >= 0; i--) facl_inv[i] = facl_inv[i + 1] * (i + 1);
    }
    Mint combination(int N, int K) {
        if (N < 0 || K < 0 || N < K) return 0;
        return facl[N] * facl_inv[N - K] * facl_inv[K];
    }
    Mint permutation(int N, int K) {
        if (N < 0 || K < 0 || N < K) return 0;
        return facl[N] * facl_inv[N - K];
    }
};

// a^0, a^1, ... , a^nを前計算する
// problem : https://atcoder.jp/contests/abc171/submissions/31917283
template <class Mint> vector<Mint> a_power_n(long long a, int n) {
    vector<Mint> res(n + 1, 1);
    for (int i = 1; i <= n; i++) res[i] = res[i - 1] * a;
    return res;
}
