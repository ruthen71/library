#include <bits/stdc++.h>
using namespace std;

// clang-format off
//#include <atcoder/modint>
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
//const ll dx[8] = {1, 0, -1, 0, 1, -1, -1, 1};
//const ll dy[8] = {0, 1, 0, -1, 1, 1, -1, -1};
template<class T> bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T> bool chmin(T &a, const T &b) { if (a>b) { a=b; return 1; } return 0; }
template<typename T> T minV(const vector<T> &x) { return *min_element(all(x)); }
template<typename T> T maxV(const vector<T> &x) { return *max_element(all(x)); }
template<class T, class U> ostream &operator<<(ostream &os, const pair<T, U> &p) { return os << "(" << p.fi << ", " << p.se << ")"; }
template<class T> ostream &operator<<(ostream &os, const vector<T> &v) { os << "[ "; for (auto &z : v) os << z << ","; os << "]"; return os; }
#ifdef _DEBUG
#define show(x) cout << #x << " = " << x << endl;
#else
#define show(x)
#endif
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return (a / gcd(a, b)) * b; }
ll rem(ll a, ll b) { return (a % b + b) % b; }
// clang-format on

// using mint = modint998244353;
// using mint = modint1000000007;

ll modpow(ll a, ll N, ll mod) {
    ll res = 1;
    // 例えば3=101(2)なので、下位bitから順に1ならa倍する
    while (N) {
        if (N & 1) res = res * a % mod;
        a = a * a % mod;
        N >>= 1;
    }
    return res;
}

struct edge {
    ll to, cost;
};

void dfs1(V2<edge> &g, int cur, int par, vll &dist) {
    for (edge &es : g[cur]) {
        if (es.to == par) continue;
        dfs1(g, es.to, cur, dist);
        chmax(dist[cur], dist[es.to] + es.cost);
    }
    return;
}

void dfs12(V2<edge> &g, int cur, int par, vll &dist, vll &ans, ll d_par) {
    ll d_max = 0;
    vector<pll> d_child;
    d_child.push_back({0, -1});  // 番兵(葉など、出次数1の場合に対応)
    for (edge &es : g[cur]) {
        // 基本的にはelseの処理をする
        // d_parに「親から見た部分木の中で、curを除き、最も距離が遠いものの距離」が入っている
        // 次に見る点が親(par)だった場合、d_par+[親とcurとの距離]になる
        if (es.to == par)
            d_child.push_back({d_par + es.cost, par});
        else
            d_child.push_back({dist[es.to] + es.cost, es.to});
    }
    sort(all(d_child));
    reverse(all(d_child));
    ans[cur] = d_child[0].first + d_child[1].first;
    for (edge &es : g[cur]) {
        if (es.to == par) continue;
        // 基本的にはd_child[0].firstが根をcurとした部分木の中で最も距離が長いもので、これを渡す
        // その部分木の根はd_child[0].second
        // これが次に訪れる予定の点に一致すると、実質同じ部分木×2の足し算になってしまうので、対処
        if (es.to == d_child[0].second)
            dfs12(g, es.to, cur, dist, ans, d_child[1].first);
        else
            dfs12(g, es.to, cur, dist, ans, d_child[0].first);
    }
}

int main() {
    ll n;
    cin >> n;
    V2<edge> g(n);
    rep(i, n - 1) {
        int s, t, w;
        cin >> s >> t >> w;
        g[s].push_back({t, w});
        g[t].push_back({s, w});
    }
    vll dist(n, 0), ans(n, 0);
    dfs1(g, 0, -1, dist);
    dfs12(g, 0, -1, dist, ans, 0);
    ll out = maxV(ans);
    cout << out << endl;
    return 0;
}

/*
全方位木DP
参考
https://ei1333.hateblo.jp/entry/2017/04/10/224413

*/
