// 自然数Nの約数列挙(O(√N))
// verified
// ABC 180 C - Cream puff
// https://atcoder.jp/contests/abc180/submissions/17488883

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long;

vector<ll> divisor(ll N) {
    vector<ll> RES;
    for (ll I = 1; I*I <= N; I++) {
        if (N%I == 0) {
            RES.push_back(I);
            if (I != N/I) RES.push_back(N/I);
        }
    }
    sort(RES.begin(), RES.end());
    return RES;
}

int main() {
    ll n; cin >> n;
    vector<ll> div = divisor(n);
    for (auto d : div) {
        printf("%lld\n", d);
    }
}
