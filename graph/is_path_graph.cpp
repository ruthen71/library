#include <bits/stdc++.h>
using namespace std;

#include <atcoder/dsu>

// パスグラフ <=> 次数が2以下かつループなし
// 多重辺,自己ループはないと仮定
// problem : https://atcoder.jp/contests/abc231/submissions/31905435
bool is_path_graph(vector<vector<int>>& G, bool single = false) {
    int N = (int)G.size();
    atcoder::dsu uf(N);
    vector<int> deg(N, 0);
    for (int a = 0; a < N; a++) {
        for (auto& b : G[a]) {
            if (a >= b) continue;
            if (uf.same(a, b)) return false;
            deg[a]++;
            deg[b]++;
            uf.merge(a, b);
        }
    }
    for (int a = 0; a < N; a++) {
        if (deg[a] > 2) return false;
    }
    if (single) {
        return uf.size(0) == N;
    }
    return true;
}
