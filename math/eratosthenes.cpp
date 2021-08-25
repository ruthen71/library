// エラトステネスの篩
// verified
// AOJ 0009 素数
// https://onlinejudge.u-aizu.ac.jp/status/users/ruthen71/submissions/1/0009/judge/4939769/C++17


#include <iostream>
#include <vector>

using namespace std;


// n以下の非負整数を入れると素数か判定する配列を返す(長さn)
vector<bool> Era(int n) {
    vector<bool> isprime(n+1,1);
    isprime[0] = 0; isprime[1] = 0;
    for (int i = 2; i < n+1; i++) {
        if (isprime[i]) {
            for (int j = 2*i; j < n+1; j += i) isprime[j] = 0;
        }
    }
    return isprime;
}

// n以下の素数の配列を返す(長さはnより小さい)
vector<int> Era_list(int n) {
    vector<bool> isprime(n+1,1);
    vector<int> res;
    isprime[0] = 0; isprime[1] = 0;
    for (int i = 2; i < n+1; i++) {
        if (isprime[i]) {
            res.push_back(i);
            for (int j = 2*i; j < n+1; j += i) isprime[j] = 0;
        }
    }
    return res;
}

int main() {
    int n;
    vector<bool> a = Era(1000100);
    vector<int> cum(1000101, 0);
    for (int i = 0; i < 1000100; i++) {
        cum[i+1] += cum[i];
        if (a[i+1]) cum[i+1]++;
    }
    while (cin >> n) {
        printf("%d\n", cum[n]);
    }
    return 0;
}

