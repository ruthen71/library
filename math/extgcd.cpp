// 拡張ユークリッドの互除法
// verified
// AOJ NTL_1_E Extended Euclid Algorithm
// https://onlinejudge.u-aizu.ac.jp/status/users/ruthen71/submissions/1/NTL_1_E/judge/5131147/C++14

#include <bits/stdc++.h>
using namespace std;

using ll = long long int;

ll extgcd(ll a, ll b, ll &x, ll &y) {
    ll d = a;
    if (b != 0) {
        d = extgcd(b, a % b, y, x);
        y -= (a / b) * x;
    } else {
        x = 1; y = 0;
    }
    return d;
}


int main() {
    ll a, b; cin >> a >> b;
    ll x, y;
    extgcd(a, b, x, y);
    cout << x << " " << y << endl;
    return 0;
}