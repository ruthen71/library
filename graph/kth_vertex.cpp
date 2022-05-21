#include <bits/stdc++.h>

int kth_vertex(std::vector<int> &a, long long K, int s) {
    // K <= 10^18
    int LOG = 60;
    int N = (int)a.size();
    std::vector<std::vector<int>> db(LOG, std::vector<int>(N));
    db[0] = a;
    for (int k = 0; k < LOG - 1; k++) {
        for (int i = 0; i < N; i++) {
            db[k + 1][i] = db[k][db[k][i]];
        }
    }
    for (int k = 0; k < LOG; k++) {
        if (K >> k & 1) {
            s = db[k][s];
        }
    }
    return s;
}

std::vector<int> kth_vertex_many(std::vector<int> &a, std::vector<std::pair<int, long long>> &sk) {
    // K <= 10^18
    int LOG = 60;
    int N = (int)a.size();
    std::vector<std::vector<int>> db(LOG, std::vector<int>(N));
    db[0] = a;
    for (int k = 0; k < LOG - 1; k++) {
        for (int i = 0; i < N; i++) {
            db[k + 1][i] = db[k][db[k][i]];
        }
    }
    int M = (int)sk.size();
    std::vector<int> res(M);
    for (int i = 0; i < M; i++) {
        auto &[s, K] = sk[i];
        for (int k = 0; k < LOG; k++) {
            if (K >> k & 1) {
                s = db[k][s];
            }
        }
        res[i] = s;
    }
    return res;
}

// K 回移動後にどこにいるかを返す
// A[i] : i->A[i]に辺が貼られている
// K <= 10^18
// https://atcoder.jp/contests/abc167/tasks/abc167_d
// https://yukicoder.me/problems/no/1935
