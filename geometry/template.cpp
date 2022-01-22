#include <bits/stdc++.h>
using namespace std;

// はじめに
using Double = double;
const Double EPS = 1e-8;
const Double PI = acos(-1);
inline int sign(const Double &x) { return x <= -EPS ? -1 : (x >= EPS ? 1 : 0); }
inline bool equals(const Double &a, const Double &b) { return sign(a - b) == 0; }

// 点
using Point = complex<Double>;
// Point operator*(const Point &p, const Double &d) { return Point(p.real() * d, p.imag() * d); }  // 定数を掛ける
// Point operator/(const Point &p, const Double &d) { return Point(p.real() / d, p.imag() / d); }  // 定数で割る
istream &operator>>(istream &is, Point &p) {
    Double x, y;
    is >> x >> y;
    p = Point(x, y);
    return is;
}
Double dot(const Point &a, const Point &b) { return a.real() * b.real() + a.imag() * b.imag(); }    // 内積
Double cross(const Point &a, const Point &b) { return a.real() * b.imag() - a.imag() * b.real(); }  // 外積

// 直線
struct Line {
    Point a, b;
    Line() = default;
    Line(Point a, Point b) : a(a), b(b) {}
    friend ostream &operator<<(ostream &os, const Line &p) { return os << p.a << "->" << p.b; }
    friend istream &operator>>(istream &is, Line &p) { return is >> p.a >> p.b; }
};

// 線分
struct Segment : Line {
    Segment() = default;
    Segment(Point a, Point b) : Line(a, b) {}
};

// 円
struct Circle {
    Point o;
    Double r;
    Circle() = default;
    Circle(Point o, Double r) : o(o), r(r) {}
    friend ostream &operator<<(ostream &os, const Circle &c) { return os << c.o << " " << c.r; }
    friend istream &operator>>(istream &is, Circle &c) { return is >> c.o >> c.r; }  // (x,y),rの順
};

// 射影(projection):CGL_1_A
// 直線lに点pから引いた垂線の足を求める
Point projection(const Line &l, const Point &p) {
    Double t = dot(p - l.a, l.b - l.a) / norm(l.b - l.a);
    return l.a + t * (l.b - l.a);
}

// 反射(reflection):CGL_1_B
// 直線lについて点pと線対称の点を求める
Point reflection(const Line &l, const Point &p) { return p + (projection(l, p) - p) * 2.0; }

// 反時計回り(ccw):CGL_1_C
// 点a,b,cの位置関係を調べる(aを基準とする)
constexpr int COUNTER_CLOCKWISE = 1;  // a-b-cが反時計回り
constexpr int CLOCKWISE = -1;         // a-b-cが時計回り
constexpr int ONLINE_BACK = 2;        // c-a-b(一直線上)
constexpr int ONLINE_FRONT = -2;      // a-b-c(一直線上)
constexpr int ON_SEGMENT = 0;         // a-c-b(一直線上)
int ccw(const Point &a, Point b, Point c) {
    b = b - a, c = c - a;
    if (sign(cross(b, c)) == 1) return COUNTER_CLOCKWISE;
    if (sign(cross(b, c)) == -1) return CLOCKWISE;
    if (sign(dot(b, c)) == -1) return ONLINE_BACK;
    if (norm(b) < norm(c)) return ONLINE_FRONT;
    return ON_SEGMENT;
}

// 平行・垂直(parallel/orthogonal):CGL_2_A
// 2直線l1,l2が平行・垂直か判定する(それぞれ外積・内積が0)
bool is_parallel(const Line &l1, const Line &l2) { return sign(cross(l1.b - l1.a, l2.b - l2.a)) == 0; }
bool is_orthogonal(const Line &l1, const Line &l2) { return sign(dot(l1.b - l1.a, l2.b - l2.a)) == 0; }
