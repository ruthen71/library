// 行列累乗
// AOJ 1327 One-Dimensional Cellular Automaton
// https://onlinejudge.u-aizu.ac.jp/status/users/ruthen71/submissions/1/1327/judge/5136734/C++14


#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i,n) for (int i = 0; i < (n); i++)

ll M;

// A*Bの計算
vector<vector<ll>> mul(vector<vector<ll>> &A, vector<vector<ll>> &B) {
    vector<vector<ll>> C(A.size(), vector<ll>(B[0].size(), 0));
    rep(i, A.size()) rep(k, B.size()) rep(j, B[0].size()) {
        C[i][j] = (C[i][j] + A[i][k]*B[k][j]) % M;
    }
    return C;
}

// A^nの計算
vector<vector<ll>> matpow(vector<vector<ll>> A, ll n) {
    vector<vector<ll>> B(A.size(), vector<ll>(A.size()));
    rep(i, A.size()) B[i][i] = 1;
    while (n) {
        if (n&1) B = mul(B, A);
        A = mul(A, A);
        n >>= 1;
    }
    return B;
}

ll N, a, b, c, t;

void solve() {
    cin >> M >> a >> b >> c >> t;
    vector<ll> S(N);
    rep(i,N) cin >> S[i];
    vector<vector<ll>> A(N, vector<ll>(N));
    rep(i,N) {
        if (i-1 >= 0) A[i][i-1] = a;
        if (i+1 < N) A[i][i+1] = c;
        A[i][i] = b;
    }
    A = matpow(A, t);
    vector<ll> T(N, 0);
    rep(i,N) {
        rep(j,N) {
            T[i] += S[j]*A[i][j];
            T[i] %= M;
        }
    }
    rep(i,N) {
        if (i == N-1) printf("%lld\n", T[i]);
        else printf("%lld ", T[i]);
    }
    return;
}

int main() {
    while (1) {
        cin >> N;
        if (N == 0ll) break;
        solve();
    }
    return 0;
}


/*
使えそうなもの

単位行列
vector<vector<ll>> E = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

アフィン変換(平行移動)
vector<vector<ll>> slide(ll px, ll py) {
    vector<vector<ll>> ret = E;
    ret[0][2] = px;
    ret[1][2] = py;
    return ret;
}
*/