#include <bits/stdc++.h>

// 転倒数 (Inversion number)
// https://en.wikipedia.org/wiki/Inversion_(discrete_mathematics)
// submission
// https://atcoder.jp/contests/abc261/submissions/33479789
// https://atcoder.jp/contests/chokudai_S001/submissions/33479816
// ご所望の場合は座圧も行います

#include <atcoder/fenwicktree>
template <class T> long long inversion_number(std::vector<T>& A, bool is_compressed) {
    int N = (int)A.size();
    if (!is_compressed) {
        std::vector<T> B = A;
        sort(B.begin(), B.end());
        B.erase(unique(B.begin(), B.end()), B.end());
        for (auto& ai : A) ai = lower_bound(B.begin(), B.end(), ai) - B.begin();
    }
    atcoder::fenwick_tree<int> fen(N);
    long long ret = 0;
    for (auto& ai : A) {
        ret += fen.sum(ai + 1, N);
        fen.add(ai, 1);
    }
    return ret;
}
