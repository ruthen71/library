#include <bits/stdc++.h>
using namespace std;

// max flow
// verified: https://onlinejudge.u-aizu.ac.jp/problems/GRL_6_A
// https://onlinejudge.u-aizu.ac.jp/status/users/ruthen71/submissions/1/GRL_6_A/judge/6093346/C++14
// https://atcoder.jp/contests/abc205/submissions/27687929

// Cap: int / long long
template <class Cap>
struct ford_fulkerson {
    struct edge {
        int to;
        Cap cap;
        int rev;
    };

    int V;
    vector<vector<edge>> G;
    int timestamp;
    vector<int> used;
    ford_fulkerson(int V) : V(V), G(V), timestamp(0), used(V, -1) {}

    void add_edge(int from, int to, Cap cap) {
        G[from].push_back((edge){to, cap, (int)G[to].size()});
        G[to].push_back((edge){from, 0, (int)G[from].size() - 1});
    }

    Cap max_flow(int s, int t) { return max_flow(s, t, numeric_limits<Cap>::max()); }
    Cap max_flow(int s, int t, Cap flow_limit) {
        Cap flow = 0;
        while (1) {
            Cap f = dfs(s, t, flow_limit);
            if (f == 0) return flow;
            flow += f;
            timestamp++;
        }
    }

    Cap dfs(int v, int t, Cap f) {
        if (v == t) return f;
        used[v] = timestamp;  // seen
        for (auto &e : G[v]) {
            if (e.cap > 0 && used[e.to] != timestamp) {
                Cap d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
};
