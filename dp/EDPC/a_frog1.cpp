// EDPC A - Frog1
// https://atcoder.jp/contests/dp/submissions/17532194

#include <iostream>
#include <vector>

using namespace std;

const int INF = 1001001001;

vector<long long> Frog1(vector<long long> &H) {
    int N = H.size();
    vector<long long> DP(N,INF);
    DP[0] = 0;
    DP[1] = abs(H[1]-H[0]);
    for (int i = 2; i < N; i++) {
        DP[i] = min(DP[i-1]+abs(H[i]-H[i-1]), DP[i-2]+abs(H[i]-H[i-2]));
    }
    return DP;
}

int main() {
    int n; cin >> n;
    vector<long long> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];
    vector<long long> res = Frog1(h);
    cout << res[n-1] << endl;
    return 0;
}
