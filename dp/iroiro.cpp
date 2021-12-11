#include <bits/stdc++.h>
using namespace std;

// A_0,...,A_{N-1} 円を払える硬貨があり、X円払う必要がある
// A_0 > A_1 > ... > A_{N-1} = 1で、A_iはA_{i+1}の倍数(0<=i<N-2)
// 出す硬貨とお釣りの硬貨の枚数の和の最小値
// B=X(A進法)(気持ちを汲んでほしい)
// C_i=A_i/A_{i+1}(比はオーバーフローしない)
// https://atcoder.jp/contests/abc155/submissions/27855969
// https://atcoder.jp/contests/abc231/submissions/27855892
long long coin_payments(vector<long long>& B, vector<long long>& C) {
    int N = B.size();
    assert(N - 1 == (int)C.size());
    vector<vector<long long>> dp(N + 1, vector<long long>(2, numeric_limits<long long>::max() / 4));
    dp[0][0] = 0;
    for (int i = 0; i < N; i++) {
        dp[i + 1][0] = min(dp[i + 1][0], dp[i][0] + B[i]);
        dp[i + 1][1] = min(dp[i + 1][1], dp[i][0] + B[i] + 1);
        if (i) dp[i + 1][0] = min(dp[i + 1][0], dp[i][1] + C[i - 1] - B[i]);
        if (i) dp[i + 1][1] = min(dp[i + 1][1], dp[i][1] + C[i - 1] - B[i] - 1);
    }
    return dp[N][0];
}
