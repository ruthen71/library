// \sum_{i=1}^{N} floor(N/i)
// O(sqrt(N))
// https://atcoder.jp/contests/abc230/submissions/27686117
long long fraction_floor_sum(long long N) {
    long long ret = 0, cur = 0;
    for (long long i = 1; i * i <= N; i++) {
        ret += N / i;
        cur = i;
    }
    for (long long i = cur; i >= 1; i--) {
        ret += i * (N / i - cur);
        cur = N / i;
    }
    return ret;
}
