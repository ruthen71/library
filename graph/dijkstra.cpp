// dijkstra法(O(ElogV))
// verified
// AOJ GRL_1_A Single Source Shortest Path
// https://onlinejudge.u-aizu.ac.jp/status/users/ruthen71/submissions/1/GRL_1_A/judge/4939121/C++17
// https://onlinejudge.u-aizu.ac.jp/status/users/ruthen71/submissions/1/GRL_1_A/judge/6364308/C++14
// https://onlinejudge.u-aizu.ac.jp/status/users/ruthen71/submissions/1/GRL_1_A/judge/6436631/C++17
// 蟻本 p97

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

template <class T> vector<T> dijkstra(vector<vector<pair<int, T>>> &G, int S) {
    int N = (int)G.size();
    const T INF = numeric_limits<T>::max();
    vector<T> dist(N, INF);
    dist[S] = 0;
    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> que;
    que.push({0, S});
    while (!que.empty()) {
        auto [d, v] = que.top();
        que.pop();
        if (dist[v] != d) continue;  // dist[v] < d
        for (auto &[nex, cost] : G[v]) {
            if (dist[nex] > d + cost) {
                dist[nex] = d + cost;
                que.push({dist[nex], nex});
            }
        }
    }
    return dist;
}

// dijkstra で求めた最短経路上で使われる辺の集合の1つを返す(全域木)
// ある頂点への最短経路が2つ以上ある場合、いずれかの経路に含まれる辺の1本を返す
// problem : https://atcoder.jp/contests/abc252/submissions/31883605
template <class T> vector<tuple<int, int, T>> dijkstra_tree(vector<vector<pair<int, T>>> &G, int S) {
    int N = (int)G.size();
    const T INF = numeric_limits<T>::max();
    vector<T> dist(N, INF);
    dist[S] = 0;
    vector<int> prev(N, -1);
    vector<tuple<int, int, T>> res;
    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> que;
    que.push({0, S});
    while (!que.empty()) {
        auto [d, v] = que.top();
        que.pop();
        if (dist[v] != d) continue;  // dist[v] < d
        if (prev[v] != -1) {
            // add edge (prev[v] -> v)
            res.push_back({prev[v], v, dist[v] - dist[prev[v]]});
        }
        for (auto &[nex, cost] : G[v]) {
            if (dist[nex] > d + cost) {
                dist[nex] = d + cost;
                prev[nex] = v;
                que.push({dist[nex], nex});
            }
        }
    }
    return res;
}