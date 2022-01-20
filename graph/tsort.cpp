// トポロジカルソート(O(V+E))
// verified
// AOJ GRL_4_B Topological Sort
// https://onlinejudge.u-aizu.ac.jp/status/users/ruthen71/submissions/1/GRL_4_B/judge/4925296/C++17

// topological sort の数え上げはbitDPでできる(ABC 041 D)

#include <bits/stdc++.h>
using namespace std;

vector<int> topological_sort(vector<vector<int>> &G) {
    int N = (int)G.size();
    vector<int> deg(N, 0);
    // 入次数をメモ
    for (int i = 0; i < N; i++) {
        for (int &v : G[i]) deg[v]++;
    }
    // 入次数0の点の集合を作成
    queue<int> que;
    for (int i = 0; i < N; i++) {
        if (deg[i] == 0) que.push(i);
    }
    vector<int> res;
    while (!que.empty()) {
        int v = que.front();
        que.pop();
        res.push_back(v);
        for (int &nx : G[v]) {
            // 入次数を減らす
            deg[nx]--;
            // 新たな入次数0の点を追加
            if (deg[nx] == 0) que.push(nx);
        }
    }
    return res;
}

int dag_longest_path_length(vector<vector<int>> &g, vector<int> &topo) {
    if (topo.size() != g.size()) return -1;
    int n = (int)g.size();
    vector<int> dp(n, 0);
    for (int &v : topo) {
        for (int &nx : g[v]) {
            dp[nx] = max(dp[nx], dp[v] + 1);
        }
    }
    return *max_element(dp.begin(), dp.end());
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
    }
    vector<int> order = topological_sort(g);
    for (int i : order) printf("%d\n", i);
    return 0;
}
