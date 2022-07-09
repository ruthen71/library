#include <bits/stdc++.h>

// ランレングス圧縮
// https://atcoder.jp/contests/abc259/tasks/abc259_c
std::vector<std::pair<char, int>> run_length_encoding(std::string &S) {
    assert(S.size() != 0);
    char las = S[0];
    std::vector<std::pair<char, int>> res;
    int cnt = 0;
    for (int i = 0; i < (int)S.size(); i++) {
        if (S[i] == las) {
            cnt++;
        } else {
            res.push_back({las, cnt});
            cnt = 1;
            las = S[i];
        }
    }
    res.push_back({las, cnt});
    return res;
}
