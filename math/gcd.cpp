// 最大公約数を求める(O(logN))
// verified
// AOJ NTL_1_C Least Common Multiple
// https://onlinejudge.u-aizu.ac.jp/status/users/ruthen71/submissions/1/NTL_1_C/judge/4985603/C++17

#include <iostream>

using namespace std;

using ll = long long;

ll gcd(ll A, ll B) {return B ? gcd(B, A%B) : A;}
ll lcm(ll A, ll B) {return (A / gcd(A, B)) * B;}

int main() {
    int n; cin >> n;
    long long a[n];
    for (int i = 0; i < n; i++) cin >> a[i];
    long long ans = 1ll;
    for (int i = 0; i < n; i++) {
        ans = lcm(ans, a[i]);
    }
    cout << ans << endl;
    return 0;
}
