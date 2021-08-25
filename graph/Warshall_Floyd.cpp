// Warshall-Floyd法(O(V^3))
// verified
// AOJ GRL_1_C All Pairs Shortest Path
// https://onlinejudge.u-aizu.ac.jp/status/users/ruthen71/submissions/1/GRL_1_C/judge/4991643/C++14
// 蟻本 p98

#include <iostream>
#include <vector>

using namespace std;

const long long INFL = 1001001001001001000;

int main() {
    int v, e; cin >> v >> e;
    vector<vector<long long>> dist(v, vector<long long>(v, INFL));

    // initialize
    for (int i = 0; i < v; i++) dist[i][i] = 0;

    // input
    for (int i = 0; i < e; i++) {
        int s, t;
        long long d;
        cin >> s >> t >> d;
        dist[s][t] = min(dist[s][t], d);
    }

    // calculate Warshall-Floyd
    for (int k = 0; k < v; k++) {
        for (int i = 0; i < v; i++) {
            for (int j = 0; j < v; j++) {
                if (dist[i][k] == INFL || dist[k][j] == INFL) continue; // 負の辺があるとき
                dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
            }
        }
    }

    // find negative cycle
    for (int i = 0; i < v; i++) {
        if (dist[i][i] < 0) {
            puts("NEGATIVE CYCLE");
            return 0;
        }
    }

    // output
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            if (dist[i][j] == INFL) printf("INF");
            else printf("%lld", dist[i][j]);
            if (j != v-1) printf(" ");
            else printf("\n");
        }
    }
    return 0;
}
