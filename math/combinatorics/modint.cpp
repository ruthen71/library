#include <bits/stdc++.h>
using namespace std;

// ref:https://www.dropbox.com/s/1zxohqaxrb87uft/Gifted_Infants_The_University_of_Tokyo___erated_files-job_14.pdf
// using mint = ModInt<998244353>;
template <uint Modulus>
struct ModInt {
    uint v;
    ModInt(long long _v = 0) { set_v(_v % Modulus + Modulus); }
    ModInt& set_v(uint _v) {
        v = (_v < Modulus) ? _v : _v - Modulus;
        return *this;
    }
    ModInt operator-() const { return ModInt() - *this; }
    ModInt operator+(const ModInt& r) const { return ModInt().set_v(v + r.v); }
    ModInt operator-(const ModInt& r) const { return ModInt().set_v(v + Modulus - r.v); }
    ModInt operator*(const ModInt& r) const { return ModInt().set_v((unsigned long long)(v)*r.v % Modulus); }
    ModInt operator/(const ModInt& r) const { return *this * r.inv(); }
    ModInt& operator+=(const ModInt& r) { return *this = *this + r; }
    ModInt& operator-=(const ModInt& r) { return *this = *this - r; }
    ModInt& operator*=(const ModInt& r) { return *this = *this * r; }
    ModInt& operator/=(const ModInt& r) { return *this = *this / r; }
    bool operator==(const ModInt& r) const { return v == r.v; }
    ModInt pow(long long n) const {
        ModInt x = *this, r = 1;
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
    ModInt inv() const { return pow(Modulus - 2); }
    friend ostream& operator<<(ostream& os, const ModInt& r) { return os << r.v; }
};
