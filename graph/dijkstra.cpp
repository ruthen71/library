// dijkstra法(O(ElogV))
// verified
// AOJ GRL_1_A Single Source Shortest Path
// https://onlinejudge.u-aizu.ac.jp/status/users/ruthen71/submissions/1/GRL_1_A/judge/4939121/C++17
// 蟻本 p97

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

using ll = long long;

const ll INF = 1ll << 60;

vector<ll> dijkstra(vector<vector<pair<int, ll>>> &G, int S) {
    int V = (int)G.size();
    vector<ll> dist(V, INF);
    dist[S] = 0;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> que;
    que.push({0, S});
    while (!que.empty()) {
        auto p = que.top();
        que.pop();
        int v = p.second;
        if (dist[v] < p.first) continue;
        for (auto &es : G[v]) {
            if (dist[es.first] > dist[v] + es.second) {
                dist[es.first] = dist[v] + es.second;
                que.push({dist[es.first], es.first});
            }
        }
        return dist;
    }
}

int main() {
    int V, E, r, s, t;
    cin >> V >> E >> r;
    ll d;
    vector<vector<pair<int, ll>>> g(V);
    for (int i = 0; i < E; i++) {
        cin >> s >> t >> d;
        g[s].push_back({t, d});
    }
    vector<ll> dist = dijkstra(g, r);
    for (int i = 0; i < V; i++) {
        if (dist[i] != INF)
            printf("%lld\n", dist[i]);
        else
            puts("INF");
    }
    return 0;
}
