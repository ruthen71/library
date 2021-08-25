// 二項係数関係のいろいろ

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
ll mod = 1000000007;
#define rep(i,n) for (ll i = 0; i < (n); i++)


ll modpow(ll A, ll N, ll mod) {
    ll RES = 1;
    // 例えば3=101(2)なので、下位bitから順に1ならa倍する
    while (N) {
        if (N & 1) RES = RES * A % mod;
        A = A * A % mod;
        N >>= 1;
    }
    return RES;
}

// nCr(mod)(O(r))
ll comb(ll N, ll R, ll mod) {
    if (N < 0 || R < 0 || N < R) return 0;
    // numerator/denominator
    ll NUME = 1, DENO = 1;
    R = min(R, N-R);
    for (int i = 1; i <= R; i++) {
        NUME = NUME * N % mod;
        DENO = DENO * i % mod;
        N--;
    }
    return NUME * modpow(DENO, mod-2, mod) % mod;
}

// modを取らないやつ
vector<ll> prime_list(ll n) {
    vector<ll> res;
    for (ll i = 2; i*i <= n; i++) {
        while (n%i == 0) {
            res.push_back(i);
            n /= i;
        }
    }
    if (n != 1ll) res.push_back(n);
    return res;
}
ll comb2(ll N, ll R) {
    ll ret = 1;
    R = min(R, N-R);
    vector<ll> nume(R);
    map<ll, ll> mp;
    rep(i,R) {
        vector<ll> pr = prime_list(N-i);
        for (auto x : pr) {
            mp[x]++;
        }
    }
    rep(i,R) {
        vector<ll> pr = prime_list(i+1);
        for (auto x : pr) {
            mp[x]--;
        }
    }
    for (auto x : mp) {
        rep(i,x.second) ret *= x.first;
    }
    return ret;
}

// nC0からnCnまで(O(n))


// nCrで、nがaからbまで変化してrが一定
// 余談だけどrCr+(r+1)Cr+…+(r+a)Cr=(r+a)C(r+1)だったりする
// (累積和みたいなことをパスカルの三角形上でしているため)
// ABC 151 E - Max-Min Sums
// https://atcoder.jp/contests/abc151/submissions/17704207
vector<ll> comb_from_aCr_to_bCr(ll a, ll b, ll r, ll mod) {
    vector<ll> res(b-a+1);
    res[0] = comb(a, r, mod);
    for (int i = 0; i < b-a; i++) {
        res[i+1] = res[i] * (a+i+1) % mod * modpow(i+1, mod-2, mod) % mod;
    }
    return res;
}

int main() {
    ll n, k; cin >> n >> k;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    sort(a.begin(), a.end());

    vector<ll> comb = comb_from_aCr_to_bCr(k-1, n, k-1, mod);
    
    ll ansM = 0;
    for (int i = 0; i < n-k+1; i++) {
        ansM += a[i+k-1] * comb[i] % mod;
        ansM %= mod;
    }
    reverse(a.begin(), a.end());
    
    ll ansm = 0;
    for (int i = 0; i < n-k+1; i++) {
        ansm += a[i+k-1] * comb[i] % mod;
        ansm %= mod;
    }
    ll ans = (ansM - ansm + mod) % mod;
    cout << ans << endl;
    return 0;
}

