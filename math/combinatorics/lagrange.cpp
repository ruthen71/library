#include <bits/stdc++.h>
using namespace std;

// 除算回数を減らした実装(Nyaanさんのものを参考にした)
// 点(x[0],y[0]),...,(x[N],y[N])を通るN次多項式P(x)に対し、P(T)を求める
// xは等差数列,N=0以上
template <class Mint>
Mint lagrange_interpolation(vector<Mint> &x, vector<Mint> &y, long long T) {
    assert(x.size() > 0);
    int N = x.size() - 1;  // degree
    Mint d = x[1] - x[0];  // x[i]=x[0]+i*d(verified:d=1,2)
    vector<Mint> invfac(N + 1, 1);
    Mint fac = 1;
    for (int i = 1; i <= N; i++) fac *= (i * d);
    invfac[N] = fac.inv();
    for (int i = N - 1; i > 0; i--) invfac[i] = invfac[i + 1] * (i + 1) * d;
    // dp=左からの累積積,pd=右からの累積積
    vector<Mint> dp(N + 1, 1), pd(N + 1, 1);
    for (int i = 1; i <= N; i++) dp[i] = dp[i - 1] * (T - x[i - 1]);
    for (int i = N - 1; i >= 0; i--) pd[i] = pd[i + 1] * (T - x[i + 1]);
    Mint ret = 0;
    for (int i = 0; i <= N; i++) {
        Mint tmp = y[i] * dp[i] * pd[i] * invfac[i] * invfac[N - i];
        if ((N - i) & 1) tmp *= -1;
        ret += tmp;
    }
    return ret;
}

using ll = long long;
using ld = long double;
#define rep(i, n) for (ll i = 0; i < (n); i++)

//点(x[0], y[0]), ... , (x[n+1], y[n+1])からn次多項式にTを代入した値f(T)を求める
// O(N^2)
// https://onlinejudge.u-aizu.ac.jp/status/users/ruthen71/submissions/1/1328/judge/5161214/C++14
ld Lagrange(vector<ld> &x, vector<ld> &y, ld T) {
    ld ret = 0;
    rep(i, x.size()) {
        ld t = 1;
        rep(j, x.size()) {
            if (i == j) continue;
            t *= T - x[j];
            t /= x[i] - x[j];
        }
        ret += t * y[i];
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
            t *= T - x[j] + mod;
            t %= mod;
            t *= modpow(x[i] - x[j] + mod, mod - 2, mod);
            t %= mod;
        }
        ret += t * y[i] % mod;
        ret %= mod;
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
    ll n = (int)(x.size()) - 1;
    rep(j, n + 1) {
        if (j == 0) continue;
        t *= T - x[j] + mod;
        t %= mod;
        t *= modpow(x[0] - x[j] + mod, mod - 2, mod);
        t %= mod;
    }
    ret += t * y[0] % mod;
    ret %= mod;
    rep(i, n) {
        t *= (T - i + mod);
        t %= mod;
        t *= modpow(T - i - 1 + mod, mod - 2, mod);
        t %= mod;
        t *= (i - n + mod);
        t %= mod;
        t *= modpow(i + 1, mod - 2, mod);
        t %= mod;
        ret += t * y[i + 1] % mod;
        ret %= mod;
    }
    return ret;
}

// modint使用
// T-x[i]==0のときの不具合を無理やり直しているのでバグってるかも
template <class Mint>
Mint lagrange_interpolation(vector<Mint> &x, vector<Mint> &y, Mint &T) {
    // 点(x[0],y[0]),...,(x[N],y[N])を通るN次多項式P(x)に対し、P(T)を求める
    assert(x.size() > 0);
    int N = x.size() - 1;  // N次多項式
    Mint basis = 1;
    for (int i = 1; i <= N; i++) {
        basis *= T - x[i];
        basis /= x[0] - x[i];
    }
    // x[k]=x0+kdの等差数列であるとする(公差d)
    Mint x0 = x[0], d = x[1] - x[0];
    Mint ret = 0;
    ret += basis * y[0];
    // ラグランジュ基底多項式の分子はT-x[i]みたいなやつがたくさんかかっている
    // 分母はx[i]-x[j]みたいなやつがたくさんかかっているが
    // 公差が一定なら少しずつしか変わらない
    for (int i = 1; i <= N; i++) {
        if (T == x[i]) return y[i];  // ゼロ除算回避
        basis *= T - x[i - 1];
        basis /= T - x[i];
        basis *= N + 1 - i;
        basis /= i;
        basis *= -1;
        ret += basis * y[i];
    }
    return ret;
}

void solve(int d) {
    //入力
    vector<ld> v(d + 3);
    rep(i, d + 3) cin >> v[i];
    //(i,v[i])が違うとする
    rep(i, d + 3) {
        vector<ld> x, y;
        int b;  //多項式推定に使わなかった値
        rep(j, d + 3) {
            if (i == j) continue;
            if (x.size() >= d + 1) {
                b = j;
                continue;
            }
            x.push_back((ld)j);
            y.push_back(v[j]);
        }
        // iについて誤差が大きく、bについて誤差はほぼないか判定
        if (abs(Lagrange(x, y, (ld)i) - v[i]) > 1e-3 && abs(Lagrange(x, y, (ld)b) - v[b]) <= 1e-3) {
            cout << i << endl;
            return;
        }
    }
    return;
}

int main() {
    while (1) {
        int d;
        cin >> d;
        if (d == 0) break;
        solve(d);
    }
    return 0;
}