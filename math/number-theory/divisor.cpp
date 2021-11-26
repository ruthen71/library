// 自然数Nの約数列挙(O(√N))
// verified
// ABC 180 C - Cream puff
// https://atcoder.jp/contests/abc180/submissions/17488883

#include <bits/stdc++.h>
using namespace std;

vector<long long> divisor(long long n) {
    vector<long long> ret;
    for (long long i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            ret.push_back(i);
            if (i != n / i) ret.push_back(n / i);
        }
    }
    sort(ret.begin(), ret.end());
    return ret;
}
