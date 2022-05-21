#include <bits/stdc++.h>
using namespace std;

// prim 法
// problem : https://onlinejudge.u-aizu.ac.jp/status/users/ruthen71/submissions/1/GRL_2_A/judge/6635206/C++17
template <class T> T prim(vector<vector<pair<int, T>>> &G) {
    int N = (int)G.size();
    vector<bool> used(N, false);
    T res = 0;
    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> que;
    que.push({0, 0});  // {cost, vertex}
    while (!que.empty()) {
        auto [c, v] = que.top();
        que.pop();
        if (used[v]) continue;  // v is already in Tree
        used[v] = true;
        res += c;
        for (auto &[nex, cost] : G[v]) {
            que.push({cost, nex});
        }
    }
    return res;
}
