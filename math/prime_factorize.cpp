// 素因数分解(O(√N))
// verified
// AOJ NTL_1_A Prime Factorize
// https://onlinejudge.u-aizu.ac.jp/status/users/ruthen71/submissions/1/NTL_1_A/judge/4983987/C++17

#include <iostream>
#include <vector>

using namespace std;

vector<long long> prime_list(long long n) {
    vector<long long> res;
    for (long long i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            res.push_back(i);
            n /= i;
        }
    }
    if (n != 1) res.push_back(n);
    return res;
}

int main() {
    long long n;
    cin >> n;
    vector<long long> plist = prime_list(n);
    printf("%lld:", n);
    for (auto p : plist) {
        printf(" %d", p);
    }
    printf("\n");
    return 0;
}