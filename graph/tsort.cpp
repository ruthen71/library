// トポロジカルソート(O(V+E))
// verified
// AOJ GRL_4_B Topological Sort
// https://onlinejudge.u-aizu.ac.jp/status/users/ruthen71/submissions/1/GRL_4_B/judge/4925296/C++17

// topological sort の数え上げはbitDPでできる(ABC 041 D)

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> tsort(vector<vector<int>> &G, int V) {
    vector<int> DEG(V,0);
    // 入次数をメモ
    for (int i = 0; i < V; i++) {
        for (int T : G[i]) DEG[T]++;
    }
    // 入次数0の点の集合を作成
    queue<int> QUE;
    for (int i = 0; i < V; i++) {
        if (DEG[i] == 0) QUE.push(i);
    }
    vector<int> RES;
    while (QUE.size()) {
        int T = QUE.front(); QUE.pop();
        RES.push_back(T);
        for (int NX : G[T]) {
            // 入次数を減らす
            DEG[NX]--;
            // 新たな入次数0の点を追加
            if (DEG[NX] == 0) QUE.push(NX);
        }
    }
    return RES;
}


int main() {
    int n,m; cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int x,y; cin >> x >> y;
        g[x].push_back(y);
    }
    vector<int> order = tsort(g,n);
    for (int i : order) printf("%d\n", i);
    return 0;
}
