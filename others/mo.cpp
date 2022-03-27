#include <bits/stdc++.h>
using namespace std;

#ifdef _RUTHEN
#include "debug.hpp"
#else
#define show(...) true
#endif

using ll = long long;
#define rep(i, n) for (int i = 0; i < (n); i++)
template <class T> using V = vector<T>;

vector<long long> prime_list_uq(long long n) {
    vector<long long> res;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            res.push_back(i);
            while (n % i == 0) n /= i;
        }
    }
    if (n != 1) res.push_back(n);
    return res;
}

#include <atcoder/modint>
using namespace atcoder;
using mint = modint998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    V<ll> A(N);
    rep(i, N) cin >> A[i];
    V<V<ll>> B(N);
    rep(i, N) B[i] = prime_list_uq(A[i]);
    V<int> cnt(1000005, 0);
    int Q;
    cin >> Q;
    V<int> L(Q), R(Q), ind(Q);
    V<mint> ans(Q);
    rep(i, Q) {
        cin >> L[i] >> R[i];
        L[i]--;
    }
    int SQ = sqrt(Q), now_l = 0, now_r = 0;
    iota(ind.begin(), ind.end(), 0);
    sort(ind.begin(), ind.end(), [&](int a, int b) {
        if (L[a] / SQ != L[b] / SQ) return L[a] < L[b];
        if (L[a] / SQ % 2 == 1) return R[a] > R[b];
        return R[a] < R[b];
    });
    mint cur = 1;
    auto add = [&](int x) {
        cur *= A[x];
        for (auto &pi : B[x]) {
            if (cnt[pi] == 0) {
                cur *= pi - 1;
                cur /= pi;
            }
            cnt[pi]++;
        }
    };
    auto del = [&](int x) {
        cur /= A[x];
        for (auto &pi : B[x]) {
            cnt[pi]--;
            if (cnt[pi] == 0) {
                cur /= pi - 1;
                cur *= pi;
            }
        }
    };
    rep(i, Q) {
        while (now_l > L[ind[i]]) add(--now_l);
        while (now_r < R[ind[i]]) add(now_r++);
        while (now_l < L[ind[i]]) del(now_l++);
        while (now_r > R[ind[i]]) del(--now_r);
        ans[ind[i]] = cur;
    }
    rep(i, Q) cout << ans[i].val() << '\n';
    return 0;
}
/**
 * 出典:TUPC2021 I
 * 適当にaddとdelを書き換えて頑張ってください
 */
