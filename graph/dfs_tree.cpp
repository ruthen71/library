#include <bits/stdc++.h>
using namespace std;

// 使用例: https://atcoder.jp/contests/abc251/submissions/31711296

vector<pair<int, int>> dfs_tree(vector<vector<int>> &G, const int s) {
    // sを根とするDFS木の一つに含まれる辺を返す
    int N = (int)G.size();
    vector<int> seen(N, 0);
    vector<pair<int, int>> res;
    auto rec = [&](auto f, int cur, int par) -> void {
        seen[cur] = 1;
        for (auto &nex : G[cur]) {
            if (nex == par) continue;
            if (seen[nex]) continue;
            res.push_back({cur, nex});
            f(f, nex, cur);
        }
    };
    rec(rec, s, -1);
    return res;
}

vector<pair<int, int>> bfs_tree(vector<vector<int>> &G, const int s) {
    // sを根とするBFS木の一つに含まれる辺を返す
    int N = (int)G.size();
    vector<int> seen(N, 0);
    vector<pair<int, int>> res;
    queue<int> que;
    que.push(s);
    seen[s] = 1;
    while (!que.empty()) {
        auto cur = que.front();
        que.pop();
        for (auto &nex : G[cur]) {
            if (seen[nex]) continue;
            res.push_back({cur, nex});
            que.push(nex);
            seen[nex] = 1;
        }
    }
    return res;
}
