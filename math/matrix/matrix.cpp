#include <bits/stdc++.h>
using namespace std;

// 参考
// https://ei1333.github.io/library/math/matrix/matrix.cpp
// https://qiita.com/gnbrganchan/items/47118d45b3af9d5ae9a4

template <class T> struct matrix {
    vector<vector<T>> A;
    matrix(int N) : A(N, vector<T>(N, 0)) {}
    matrix(int N, int M) : A(N, vector<T>(M, 0)) {}
    matrix(int N, int M, T value) : A(N, vector<T>(M, value)) {}
    int row() const { return ((int)A.size()); }     // このconstは関数内でメンバ変数に変更がないことを表す
    int col() const { return ((int)A[0].size()); }  // ないと四則演算でBがconstとして呼ばれているがrow(),col()で変更される可能性があるとしてエラーを吐く

    vector<T> &operator[](int i) { return A[i]; }              // 書込み
    const vector<T> &operator[](int i) const { return A[i]; }  // 参照
    static matrix E(int N) {                                   // 単位行列
        matrix ret(N);
        for (int i = 0; i < N; i++) ret[i][i] = 1;
        return ret;
    }
    matrix &operator+=(const matrix &B) {
        // A(N,M) + B(N,M)
        int N = row(), M = col();
        assert(N == B.row() && M == B.col());
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                (*this)[i][j] += B[i][j];
            }
        }
        return (*this);
    }
    matrix &operator-=(const matrix &B) {
        int N = row(), M = col();
        assert(N == B.row() && M == B.col());
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                (*this)[i][j] -= B[i][j];
            }
        }
        return (*this);
    }
    matrix &operator*=(const matrix &B) {
        // A(N,L) * B(L,M) = C(N,M)
        int N = row(), M = B.col(), L = B.row();
        assert(L == col());
        matrix C(N, M);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                for (int k = 0; k < L; k++) {
                    C[i][j] += (*this)[i][k] * B[k][j];
                }
            }
        }
        A.swap(C.A);
        return (*this);
    }
    matrix pow(long long n) {
        assert(row() == col());
        matrix B = matrix::E(row()), X = (*this);
        while (n > 0) {
            if (n & 1) B *= X;
            X *= X;
            n >>= 1;
        }
        A.swap(B.A);
        return (*this);
    }
    matrix operator+(const matrix &B) { return ((*this) += B); }
    matrix operator-(const matrix &B) { return ((*this) -= B); }
    matrix operator*(const matrix &B) { return ((*this) *= B); }
    friend ostream &operator<<(ostream &os, matrix &A) {
        int N = A.row(), M = A.col();
        for (int i = 0; i < N; i++) {
            os << '[';
            for (int j = 0; j < M; j++) os << A[i][j] << (j == M - 1 ? ']' : ' ');
        }
        return (os);
    }
    // matrix op T
    matrix &operator+=(const T &k) {
        int N = row(), M = col();
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++) (*this)[i][j] += k;
        return (*this);
    }
    matrix &operator-=(const T &k) {
        int N = row(), M = col();
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++) (*this)[i][j] -= k;
        return (*this);
    }
    matrix &operator*=(const T &k) {
        int N = row(), M = col();
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++) (*this)[i][j] *= k;
        return (*this);
    }
    matrix &operator/=(const T &k) {
        int N = row(), M = col();
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++) (*this)[i][j] /= k;
        return (*this);
    }
    matrix operator+(const T &k) { return ((*this) += k); }
    matrix operator-(const T &k) { return ((*this) -= k); }
    matrix operator*(const T &k) { return ((*this) *= k); }
    matrix operator/(const T &k) { return ((*this) /= k); }
};
