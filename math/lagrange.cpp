#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
#define rep(i,n) for (ll i = 0; i < (n); i++)

//点(x[0], y[0]), ... , (x[n+1], y[n+1])からn次多項式にTを代入した値f(T)を求める
//O(N^2)
// https://onlinejudge.u-aizu.ac.jp/status/users/ruthen71/submissions/1/1328/judge/5161214/C++14
ld Lagrange(vector<ld> &x, vector<ld> &y, ld T) {
    ld ret = 0;
    rep(i, x.size()) {
        ld t = 1;
        rep(j, x.size()) {
            if (i == j) continue;
            t *= T-x[j];
            t /= x[i]-x[j];
        }
        ret += t*y[i];
    }
    return ret;
}
// https://atcoder.jp/contests/arc033/submissions/19674552
// 部分点
const ll mod = 1000000007;
long long modpow(long long A, long long N, long long mod) {
    long long RES = 1;
    // 例えば3=101(2)なので、下位bitから順に1ならa倍する
    while (N) {
        if (N & 1) RES = RES * A % mod;
        A = A * A % mod;
        N >>= 1;
    }
    return RES;
}
ll Lagrange(vector<ll> &x, vector<ll> &y, ll T) {
    ll ret = 0;
    rep(i, x.size()) {
        ll t = 1;
        rep(j, x.size()) {
            if (i == j) continue;
            t *= T-x[j]+mod; t %= mod;
            t *= modpow(x[i]-x[j]+mod, mod-2, mod); t %= mod;
        }
        ret += t*y[i]%mod; ret %= mod;
    }
    return ret;
}
// https://atcoder.jp/contests/arc033/submissions/19675641
// 満点
// x_0, x_1, ..., x_nが等差数列のときに使える
// 下の関数は0, 1, ..., nのときのもの
ll Lagrange2(vector<ll> &x, vector<ll> &y, ll T) {
    ll ret = 0;
    ll t = 1;
    ll n = (int)(x.size())-1;
    rep(j, n+1) {
        if (j == 0) continue;
        t *= T-x[j]+mod; t %= mod;
        t *= modpow(x[0]-x[j]+mod, mod-2, mod); t %= mod;
    }
    ret += t*y[0]%mod; ret %= mod;
    rep(i, n) {
        t *= (T-i+mod); t %= mod;
        t *= modpow(T-i-1+mod, mod-2, mod); t %= mod;
        t *= (i-n+mod); t %= mod;
        t *= modpow(i+1, mod-2, mod); t %= mod;
        ret += t*y[i+1]%mod; ret %= mod;
    }
    return ret;
}

void solve(int d) {
    //入力
    vector<ld> v(d+3); rep(i,d+3) cin >> v[i];
    //(i,v[i])が違うとする
    rep(i,d+3) {
        vector<ld> x, y;
        int b;  //多項式推定に使わなかった値
        rep(j,d+3) {
            if (i == j) continue;
            if (x.size() >= d+1) {
                b = j;
                continue;
            }
            x.push_back((ld)j);
            y.push_back(v[j]);
        }
        //iについて誤差が大きく、bについて誤差はほぼないか判定
        if (abs(Lagrange(x, y, (ld)i) - v[i]) > 1e-3 && abs(Lagrange(x, y, (ld)b) - v[b]) <= 1e-3) {
            cout << i << endl;
            return;
        }
    }
    return;
}

int main() {
    while (1) {
        int d; cin >> d;
        if (d == 0) break;
        solve(d);
    }
    return 0;
}