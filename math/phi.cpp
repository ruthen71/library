// 自然数Nについて、1からNまでの自然数のうちnと互いに素なものの個数(O(√N))
// verified
// NTL_1_D Euler's Phi Function
// https://onlinejudge.u-aizu.ac.jp/status/users/ruthen71/submissions/1/NTL_1_D/judge/4985627/C++17
// 参考
// https://mathtrain.jp/phi

#include <iostream>

using namespace std;

long long phi(long long n) {
    // Phi(n) = nに(1-1/p_i)の総乗をかけたもの(p_iはnの素因数)
    long long res = n;
    for (long long i = 2; i*i <= n; i++) {
        if (n%i == 0) { // i is prime
            res /= i;
            res *= i-1;
            while (n%i == 0) n /= i;
        }
    }
    if (n != 1ll) {
        res /= n;
        res *= n-1;
    }
    return res;
}
int main() {
    long long n; cin >> n;
    long long ans = phi(n);
    cout << ans << endl;
    return 0;
}
