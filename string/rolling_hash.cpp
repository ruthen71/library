// ローリングハッシュ
// 文字列照合をO(m+n)でやる
// verified: https://onlinejudge.u-aizu.ac.jp/status/users/ruthen71/submissions/1/ALDS1_14_B/judge/5537079/C++14


#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

const ull B1 = 100000007;   // ハッシュの基数1
const ull B2 = 1000000007;  // ハッシュの基数2

// aはbに含まれているか？(indexを全部出力する)
bool rolling_hash(string a, string b) {
    int al = a.length(), bl = b.length();
    if (al > bl) return false;
    // B の al 乗を計算
    ull t1 = 1, t2 = 1;
    for (int i = 0; i < al; i++) {
        t1 *= B1, t2 *= B2;
    }
    // aとbの最初のal文字に関するハッシュ値を計算
    ull ah1 = 0, ah2 = 0, bh1 = 0, bh2 = 0;
    for (int i = 0; i < al; i++) {
        ah1 = ah1 * B1 + a[i], ah2 = ah2 * B2 + a[i];
        bh1 = bh1 * B1 + b[i], bh2 = bh2 * B2 + b[i];
    }
    // bの場所を1つずつ進めながらハッシュ値をチェック
    for (int i = 0; i + al <= bl; i++) {
        if (ah1 == bh1 && ah2 == bh2) {
            cout << i << endl;  // bのi文字目からのal文字が一致
            // 判定だけしたいとき
            // return true;
        }
        if (i + al < bl) {
            bh1 = bh1 * B1 + b[i + al] - b[i] * t1;
            bh2 = bh2 * B2 + b[i + al] - b[i] * t2;
        }
    }
    return false;
}

int main() {
    string s, t;
    cin >> s >> t;
    rolling_hash(t, s);
    return 0;
}
