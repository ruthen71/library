// Bellman-Ford法(O(VE))
// verified
// AOJ GRL_1_B All Pairs Shortest Path (Negative Edges)
// https://onlinejudge.u-aizu.ac.jp/status/users/ruthen71/submissions/1/GRL_1_B/judge/4991715/C++14
// 蟻本 p95
// 負閉路が存在するときに空配列を返すのは下記リンクを参考にした
// https://onlinejudge.u-aizu.ac.jp/solutions/problem/GRL_1_B/review/4301292/ei1333/C++14


#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

const ll INF = 1ll<<60;

struct edge { int from, to; ll cost; };

vector<ll> bellman_ford(vector<edge> &es, int S, int V) {
    vector<ll> b_dist(V, INF);
    b_dist[S] = 0;
    for (int i = 0; i < V-1; i++) {
        for (auto &e : es) {
            if (b_dist[e.from] == INF) continue;
            b_dist[e.to] = min(b_dist[e.to], b_dist[e.from]+e.cost);
        }
    }
    // if negative cycle exists, an empty vector will return.
    for (auto e : es) {
        if (b_dist[e.from] == INF) continue;
        if (b_dist[e.from]+e.cost < b_dist[e.to]) {
            vector<ll> res;
            return res;
        }
    }
    return b_dist;
}

int main() {
    int v, e, r; cin >> v >> e >> r;
    vector<edge> edges(e);
    for (int i = 0; i < e; i++) {
        int s, t;
        ll d;
        cin >> s >> t >> d;
        edges[i] = {s, t, d};
    }
    vector<ll> dists = bellman_ford(edges, r, v);
    if (dists.size() == 0) {
        puts("NEGATIVE CYCLE");
        return 0;
    }
    for (auto dist : dists) {
        if (dist == INF) puts("INF");
        else printf("%lld\n", dist);
    } 
    return 0;
}
