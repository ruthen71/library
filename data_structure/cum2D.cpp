// Cumulative sum 2D
// verified
// ABC 005 D - おいしいたこ焼きの焼き方
// https://atcoder.jp/contests/abc005/submissions/18634304
// ABC 106 D - AtCoder Express 2
// https://atcoder.jp/contests/abc106/submissions/18634648

// オーバーフローはするかもしれない(verifyしてない)
// マス(rx, ry)と同じ行または列にあるマスはsumに含まれない(半開区間)

#include <iostream>
#include <vector>

using namespace std;

template <class T>
struct Cum2D {
    vector<vector<T>> cum;

    Cum2D(int W, int H) : cum(W+1, vector<T>(H+1, 0)) {}

    void set(int x, int y, T z) {
        cum[x+1][y+1] = z;
    }

    T get(int x, int y) {
        return cum[x+1][y+1];
    }

    void calc() {
        for(int i = 1; i < cum.size(); i++) {
            for(int j = 1; j < cum[i].size(); j++) {
                cum[i][j] += cum[i][j-1]+cum[i-1][j]-cum[i-1][j-1];
            }
        }
    }

    T sum(int lx, int rx, int ly, int ry) {
      return (cum[rx][ry]-cum[lx][ry]-cum[rx][ly]+cum[lx][ly]);
    }

    void debug_print() {
        for (int i = 0; i < cum.size(); i++) {
            for (int j = 0; j < cum[i].size(); j++) {
                cout << cum[i][j] << ' ';
            }
            printf("\n");
        }
    }
};


// ABC 005 D - おいしいたこ焼きの焼き方
int main() {
    int n; cin >> n;
    Cum2D<int> cum(n,n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int d; cin >> d;
            cum.set(i,j,d);
        }
    }
    cum.calc();
    vector<int> ans(n*n+1, 0);
    for (int rx = 1; rx < n+1; rx++) {
        for (int lx = 0; lx < rx; lx++) {
            for (int ry = 1; ry < n+1; ry++) {
                for (int ly = 0; ly < ry; ly++) {
                    int d = cum.sum(lx, rx, ly, ry);
                    ans[(rx-lx)*(ry-ly)] = max(ans[(rx-lx)*(ry-ly)], d);
                }
            }
        }
    }
    for (int i = 0; i < n*n; i++) {
        ans[i+1] = max(ans[i], ans[i+1]);
    }
    int q; cin >> q;
    while (q--) {
        int p; cin >> p;
        cout << ans[p] << endl;
    }
    return 0;
}

// ABC 106 D - AtCoder Express 2
int main() {
    int n, m, q; cin >> n >> m >> q;
    Cum2D<int> cum(n,n);
    while (m--) {
        int l, r; cin >> l >> r;
        l--; r--;
        cum.set(l, r, cum.get(l, r)+1);
    }
    cum.calc();
    // cum.debug_print();
    while (q--) {
        int p, q; cin >> p >> q;
        p--; q--;
        cout << cum.sum(p, q+1, p, q+1) << endl;
    }
    return 0;
}