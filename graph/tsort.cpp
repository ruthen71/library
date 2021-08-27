// トポロジカルソート(O(V+E))
// verified
// AOJ GRL_4_B Topological Sort
// https://onlinejudge.u-aizu.ac.jp/status/users/ruthen71/submissions/1/GRL_4_B/judge/4925296/C++17

// topological sort の数え上げはbitDPでできる(ABC 041 D)

#include <bits/stdc++.h>
using namespace std;

// clang-format off
//#include <atcoder/all>
//using namespace atcoder;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pdd = pair<ld, ld>;
using vii = vector<int>;
using vll = vector<ll>;
using vdd = vector<ld>;
using vvii = vector<vector<int>>;
using vvll = vector<vector<ll>>;
using vvdd = vector<vector<ld>>;
using vvvii = vector<vector<vector<int>>>;
using vvvll = vector<vector<vector<ll>>>;
using vvvdd = vector<vector<vector<ld>>>;
template<class T, class U> using P = pair<T, U>;
template<class T> using V1 = vector<T>;
template<class T> using V2 = vector<vector<T>>;
template<class T> using V3 = vector<vector<vector<T>>>;
template<class T> using pque = priority_queue<T, vector<T>, greater<T>>;
#define _overload3(_1, _2, _3, name, ...) name
#define rep1(n) for (ll i = 0; i < (n); i++)
#define rep2(i, n) for (ll i = 0; i < (n); i++)
#define rep3(i, a, b) for (ll i = (a); i < (b); i++)
#define rep(...) _overload3(__VA_ARGS__, rep3, rep2, rep1)(__VA_ARGS__)
#define rrep1(n) for (ll i = (n) - 1; i >= 0; i--)
#define rrep2(i, n) for (ll i = (n) - 1; i >= 0; i--)
#define rrep3(i, a, b) for (ll i = (b) - 1; i >= (a); i--)
#define rrep(...) _overload3(__VA_ARGS__, rrep3, rrep2, rrep1)(__VA_ARGS__)
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
#define fi first
#define se second
#define pb push_back
#define endl '\n'
#define popcnt(x) __builtin_popcountll(x)
#define uniq(x) (x).erase(unique((x).begin(), (x).end()), (x).end());
#define IOS ios::sync_with_stdio(false); cin.tie(nullptr);
const int inf = 1 << 30;
const ll INF = 1ll << 60;
const ld DINF = numeric_limits<ld>::infinity();
const ll mod = 1000000007;
//const ll mod = 998244353;
const ld EPS = 1e-9;
const ld PI = 3.1415926535897932;
const ll dx[8] = {1, 0, -1, 0, 1, -1, -1, 1};
const ll dy[8] = {0, 1, 0, -1, 1, 1, -1, -1};
template<class T> bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T> bool chmin(T &a, const T &b) { if (a>b) { a=b; return 1; } return 0; }
template<typename T> T min(const vector<T> &x) { return *min_element(all(x)); }
template<typename T> T max(const vector<T> &x) { return *max_element(all(x)); }
template<class T, class U> ostream &operator<<(ostream &os, const pair<T, U> &p) { return os << "(" << p.fi << ", " << p.se << ")"; }
template<class T> ostream &operator<<(ostream &os, const vector<T> &v) { os << "[ "; for (auto &z : v) os << z << " "; os << "]"; return os; }
#ifdef _DEBUG
#define show(x) cout << #x << " = " << x << endl;
#else
#define show(x)
#endif
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return (a / gcd(a, b)) * b; }
ll rem(ll a, ll b) { return (a % b + b) % b; }
// clang-format on

vector<int> tsort(vector<vector<int>> &G, int V) {
    vector<int> DEG(V, 0);
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
        int T = QUE.front();
        QUE.pop();
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

int dagLongestPath_length(vector<vector<int>> &g, vector<int> &topo) {
    int n = (int)g.size();
    if (sz(topo) != n) return -1;
    vector<int> dp(n, 0);
    for (int v : topo) {
        for (int nx : g[v]) {
            chmax(dp[nx], dp[v] + 1);
        }
    }
    int ans = 0;
    rep(i, n) chmax(ans, dp[i]);
    return ans;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
    }
    vector<int> order = tsort(g, n);
    for (int i : order) printf("%d\n", i);
    return 0;
}
