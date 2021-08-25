// EDPC B - Frog2
// https://atcoder.jp/contests/dp/submissions/17532290

#include <iostream>
#include <vector>

using namespace std;

const int INF = 1001001001;

vector<long long> Frog2(vector<long long> &H, int K) {
    int N = H.size();
    vector<long long> DP(N,INF);
    DP[0] = 0;
    for (int i = 0; i < N; i++) {
        long long D_MIN = INF;
        for (int j = 1; (j <= K) && (i+j < N); j++) {
            DP[i+j] = min(DP[i]+abs(H[i+j]-H[i]), DP[i+j]);
        }
    }
    return DP;
}

int main() {
    int n,k; cin >> n >> k;
    vector<long long> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];
    vector<long long> res = Frog2(h,k);
    cout << res[n-1] << endl;
    return 0;
}
