#include <bits/stdc++.h>
using namespace std;

// 使用例
// https://atcoder.jp/contests/practice/submissions/28824369
// std::sort()ではダメなとき用

template <class T>
int comp(T x, T y) {
    // return x < y;
    char cx = 'A' + x, cy = 'A' + y;
    cout << "? " << cx << " " << cy << endl;
    char res;
    cin >> res;
    return res == '<';
}

template <class T>
void merge(vector<T>& a, vector<T>& b, int left, int mid, int right) {
    int i = left, j = mid, k = 0;
    while (i < mid && j < right) {
        if (comp(a[i], a[j])) {  // a[i] < a[j] なら1を返す
            b[k++] = a[i++];
        } else {
            b[k++] = a[j++];
        }
    }
    if (i == mid) {
        while (j < right) b[k++] = a[j++];
    } else {
        while (i < mid) b[k++] = a[i++];
    }
    for (int l = 0; l < k; l++) a[left + l] = b[l];
    return;
}

template <class T>
void merge_sort_inner(vector<T>& a, vector<T>& b, int l, int r) {
    if (r - l <= 1) return;
    int mid = (l + r) / 2;
    merge_sort_inner(a, b, l, mid);
    merge_sort_inner(a, b, mid, r);
    merge(a, b, l, mid, r);
    return;
}

template <class T>
void merge_sort(vector<T>& a) {
    int l = 0, r = (int)a.size();
    vector<T> b(r);
    merge_sort_inner(a, b, l, r);
    return;
}