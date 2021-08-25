// LIS(最長増加部分列問題)
// https://atcoder.jp/contests/chokudai_S001/submissions/19508576


#include <bits/stdc++.h>
using namespace std;

using ll = long long int;
#define rep(i,n) for (ll i = 0; i < (n); i++)
#define all(v) (v).begin(), (v).end()
const int INF = 1001001001;

int main() {
    int n; cin >> n;
    vector<int> a(n); rep(i,n) cin >> a[i];
    vector<int> dp(n, INF);
    rep(i,n) {
        *lower_bound(all(dp), a[i]) = a[i];
    }
    cout << lower_bound(all(dp), INF)-dp.begin() << endl;
    return 0;
}
