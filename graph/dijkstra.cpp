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
    int V = (int)G.size();
    const T INF = numeric_limits<T>::max();
    vector<T> dist(V, INF);
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

using ll = long long;

int main() {
    int V, E, r, s, t;
    cin >> V >> E >> r;
    ll d;
    vector<vector<pair<int, ll>>> g(V);
    for (int i = 0; i < E; i++) {
        cin >> s >> t >> d;
        g[s].push_back({t, d});
    }
    vector<ll> dist = dijkstra<ll>(g, r);
    for (int i = 0; i < V; i++) {
        if (dist[i] != numeric_limits<ll>::max())
            printf("%lld\n", dist[i]);
        else
            puts("INF");
    }
    return 0;
}
