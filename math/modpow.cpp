// A^Nをmodで割った余りを求める(O(logN))
// verified
// AOJ NTL_1_B Power
// https://onlinejudge.u-aizu.ac.jp/status/users/ruthen71/submissions/1/NTL_1_B/judge/4985591/C++17

#include <iostream>

using namespace std;

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

int main() {
    long long m, n, mod = 1000000007;
    cin >> m >> n;
    long long ans = modpow(m, n, mod);
    cout << ans << endl;
    return 0;
}
