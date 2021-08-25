// dijkstra法(O(ElogV))
// verified
// AOJ GRL_1_A Single Source Shortest Path
// https://onlinejudge.u-aizu.ac.jp/status/users/ruthen71/submissions/1/GRL_1_A/judge/4939121/C++17
// 蟻本 p97

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

using ll = long long;

const ll INF = 1ll<<60;

vector<ll> dijkstra(vector<vector<pair<int, ll>>> &GRAPH, int V, int S) {
    vector<ll> dist(V, INF);
    dist[S] = 0;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> que;
    que.push({0, S});

    while (!que.empty()) {
        pair<ll, int> p = que.top(); que.pop();
        int v = p.second;
        if (dist[v] < p.first) continue;
        for (int i = 0; i < GRAPH[v].size(); i++) {
            pair<int, ll> edge = GRAPH[v][i];
            if (dist[edge.first] > dist[v] + edge.second) {
                dist[edge.first] = dist[v] + edge.second;
                que.push({dist[edge.first], edge.first});
            }
        }
    }
    return dist;
}


int main() {
    int V,E,r,s,t; cin >> V >> E >> r;
    ll d;
    vector<vector<pair<int, ll>>> g(V);
    for (int i = 0; i < E; i++) {
        cin >> s >> t >> d;
        g[s].push_back({t,d});
    }
    vector<ll> dist = dijkstra(g, V, r);
    for (int i = 0; i < V; i++) {
        if (dist[i] != INF) printf("%lld\n", dist[i]);
        else puts("INF");
    }
    return 0;
}

