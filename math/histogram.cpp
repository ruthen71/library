#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i,n) for (ll i = 0; i < (n); i++)

ll histogram_largest_area(vector<ll> hist) {
    ll histsz = hist.size();
    stack<int> st1, st2;
    vector<ll> left(histsz, 0), right(histsz, 0);
    for (int i = 0; i < histsz; i++) {
        while (!st1.empty() && hist[st1.top()] >= hist[i]) st1.pop();
        if (st1.empty()) left[i] = 0;
        else left[i] = st1.top()+1;
        st1.push(i);
    }
    for (int i = histsz-1; i >= 0; i--) {
        while (!st2.empty() && hist[st2.top()] >= hist[i]) st2.pop();
        if (st2.empty()) right[i] = histsz;
        else right[i] = st2.top();
        st2.push(i);
    }
    ll ret = 0;
    for (int i = 0; i < histsz; i++) {
        ret = max(ret, hist[i]*(right[i]-left[i]));
    }
    return ret;
}

//https://atcoder.jp/contests/abc189/submissions/19589738
ll histogram_max_area(vector<long long> histogram) {
    histogram.push_back(0LL);
    stack<pair<int, ll>> st;
    st.emplace(-1, 0LL);
    ll ans = 0;
    for(int i = 0; i < histogram.size(); i++) {
        auto &t = histogram[i];
        while(!st.empty() && st.top().second > t) {
            ll height = st.top().second;
            st.pop();
            ans = max(ans, (height) * (i - st.top().first - 1));
        }
        st.emplace(i, t);
    }
    return ans;
}

int main() {
    int n; cin >> n;
    vector<ll> h(n);
    rep(i,n) cin >> h[i];
    ll ans = histogram_largest_area(h);
    cout << ans << endl;
    return 0;
}