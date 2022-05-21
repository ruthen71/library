// LIS(最長増加部分列問題)
// https://atcoder.jp/contests/chokudai_S001/submissions/19508576
// https://onlinejudge.u-aizu.ac.jp/status/users/ruthen71/submissions/1/DPL_1_D/judge/6609197/C++17

#include <bits/stdc++.h>
using namespace std;

template <class T> int longest_increasing_subsequence(const vector<T> &A, bool strict) {
    // strict = true ... A[i] < A[i+1], false ... A[i] <= A[i+1]
    int N = (int)A.size();
    const T INF = numeric_limits<T>::max();
    vector<T> dp(N, INF);
    // dp配列中にA[i]があったときに、どの値を書き換えるかを考えるとlower/upperを区別できる
    if (strict) {
        for (int i = 0; i < N; i++) {
            *lower_bound(dp.begin(), dp.end(), A[i]) = A[i];  // strictなのでその値
        }
    } else {
        for (int i = 0; i < N; i++) {
            *upper_bound(dp.begin(), dp.end(), A[i]) = A[i];  // strictではないのでその次の値
        }
    }
    return lower_bound(dp.begin(), dp.end(), INF) - dp.begin();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];
    cout << longest_increasing_subsequence<int>(A, true) << '\n';
    return 0;
}
