#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i, n) for (int i = 0; i < (n); i++)
template <class T> using V = vector<T>;

// とりあえずコード例
// 抽象化は難しいのでまだ
// problem : 木の直径 https://onlinejudge.u-aizu.ac.jp/problems/GRL_5_A
// submission : https://onlinejudge.u-aizu.ac.jp/status/users/ruthen71/submissions/1/GRL_5_A/judge/6648207/C++17
// problem : Traffic Tree https://onlinejudge.u-aizu.ac.jp/problems/1595
// submission : https://onlinejudge.u-aizu.ac.jp/status/users/ruthen71/submissions/1/1595/judge/6648225/C++17
// problem : Distributing Integers https://atcoder.jp/contests/abc160/tasks/abc160_f
// submission : https://atcoder.jp/contests/abc160/submissions/31953588

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    if (N == 1) {
        cout << 0 << '\n';
        return 0;
    }
    V<V<pair<int, ll>>> G(N);
    for (int i = 0; i < N - 1; i++) {
        int s, t, w;
        cin >> s >> t >> w;
        G[s].push_back({t, w});
        G[t].push_back({s, w});
    }
    V<ll> dp1(N, 0);  // 0を根とする根付き木のiを根とする部分木の答え
    auto dfs = [&](auto f, int cur, int par) -> void {
        for (auto &[nex, cost] : G[cur]) {
            if (nex == par) continue;
            f(f, nex, cur);
            dp1[cur] = max(dp1[cur], dp1[nex] + cost);
        }
        return;
    };
    dfs(dfs, 0, -1);
    V<ll> dp2(N);  // iを根とする根付き木のiを根とする部分木の答え
    auto rerooting = [&](auto g, int cur, int par, ll dp1_par) -> void {
        V<pair<ll, int>> dp1_cld;    // {dp1[id], id}
        dp1_cld.push_back({0, -1});  // 番兵
        for (auto &[nex, cost] : G[cur]) {
            if (nex == par) {
                dp1_cld.push_back({dp1_par + cost, par});  // curを根と見たときのparを根とする部分木に対するdp1を伝播させておく
            } else {
                dp1_cld.push_back({dp1[nex] + cost, nex});  // curを根と見たときのnexを根とする部分木に対するdp1は求められている
            }
        }
        sort(dp1_cld.rbegin(), dp1_cld.rend());
        dp2[cur] = dp1_cld[0].first + dp1_cld[1].first;
        for (auto &[nex, cost] : G[cur]) {
            if (nex == par) continue;
            if (nex == dp1_cld[0].second) {  // 適切にdp1_parとして伝播させる値を選択する
                g(g, nex, cur, dp1_cld[1].first);
            } else {
                g(g, nex, cur, dp1_cld[0].first);
            }
        }
        return;
    };
    rerooting(rerooting, 0, -1, 0);
    cout << *max_element(dp2.begin(), dp2.end()) << '\n';
    return 0;
}
