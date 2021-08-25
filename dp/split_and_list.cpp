// 半分全列挙を用いたナップサック問題(O(N 2^(N/2) ) )
// DPではない気がするけどナップサック問題の一種としてDPに追加
// verified
// ABC 184 F - Programming Contest
// https://atcoder.jp/contests/abc184/submissions/19101160
// https://atcoder.jp/contests/abc184/submissions/19102106

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    long long n, t; cin >> n >> t;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<long long> g1(1 << n/2), g2(1 << (n-n/2));

    for (int bit = 0; bit < (1 << n/2); bit++) {
        long long sum = 0;
        for (int i = 0; i < (n/2); i++) {
            if (bit>>i&1) sum += a[i];
        }
        g1[bit] = sum;
    }

    for (int bit = 0; bit < (1 << (n-n/2)); bit++) {
        long long sum = 0;
        for (int i = 0; i < (n-n/2); i++) {
            if (bit>>i&1) sum += a[i+n/2];
        }
        g2[bit] = sum;
    }

    sort(g2.begin(), g2.end());

    long long ans = 0;

    for (auto elem : g1) {
        if (elem > t) continue;
        ans = max(ans, elem + *(upper_bound(g2.begin(), g2.end(), t-elem)-1));
    }
    cout << ans << endl;
    return 0;
}

// 尺取り法とマージソートを用いたO(2^(n/2))の解法
vector<ll> merge(vector<ll>& g, ll x){ // merge g and g + x (= gg)
    vector<ll> ans, gg;
    // make gg(g+x)
    for (auto elem : g) {
        gg.push_back(elem+x);
    }
    // merge g and gg
    auto i = g.begin(), j = gg.begin();
    while (i < g.end()) {
        if ((*i) <= (*j)) ans.push_back(*i++);
        else ans.push_back(*j++);
    }
    while (j < gg.end()) ans.push_back(*j++);
    return ans;
}

int main(){
    ll n, t;
    cin >> n >> t;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<ll> g1(1,0), g2(1,0);
    for (int i = 0; i < n; i++) {
        if (i%2 == 0) g1 = merge(g1, a[i]);
        else g2 = merge(g2, a[i]);
    }

    ll ans = 0;
    int idx = int(g1.size())-1;

    for (auto elem : g2) {
        if (elem > t) break;
        while (elem+g1[idx] > t) idx--;
        ans = max(ans, elem+g1[idx]);
    }

    cout << ans << endl;
}