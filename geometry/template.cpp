// ref
// https://ei1333.github.io/library/geometry/template.cpp
// https://bakamono1357.hatenablog.com/entry/2020/04/29/025320

#include <bits/stdc++.h>
using namespace std;

// はじめに
using Double = double;
const Double EPS = 1e-8;
const Double PI = acos(-1);
inline int sign(const Double &x) { return x <= -EPS ? -1 : (x >= EPS ? 1 : 0); }
inline bool equals(const Double &a, const Double &b) { return sign(a - b) == 0; }
Double radian_to_degree(Double r) { return r * 180.0 / PI; }
Double degree_to_radian(Double d) { return d * PI / 180.0; }

// 点
using Point = complex<Double>;
istream &operator>>(istream &is, Point &p) {
    Double x, y;
    is >> x >> y;
    p = Point(x, y);
    return is;
}
Double dot(const Point &a, const Point &b) { return a.real() * b.real() + a.imag() * b.imag(); }    // 内積
Double cross(const Point &a, const Point &b) { return a.real() * b.imag() - a.imag() * b.real(); }  // 外積
Point rotate(const Point &p, const Double &theta) { return p * Point(cos(theta), sin(theta)); }
// usage: rotate(P, PI/2) ... 時計回りに90度回転
// usage: rotate(P, degree_to_radian(90)) ... 同上

// 直線
struct Line {
    Point a, b;
    Line() = default;
    Line(Point a, Point b) : a(a), b(b) {}
    Line(Double A, Double B, Double C) {
        // Ax + By = C
        if (equals(A, 0)) {
            a = Point(0, C / B), b = Point(1, C / B);
        } else if (equals(B, 0)) {
            a = Point(C / A, 0), b = Point(C / A, 1);
        } else {
            a = Point(0, C / B), b = Point(C / A, 0);
        }
    }
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
Point reflection(const Line &l, const Point &p) { return p + (projection(l, p) - p) * (Double)2.0; }

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

// 交差判定(intersection):CGL_2_B
// 2線分s1,s2が交差するか判定する
bool is_intersect_ss(const Segment &s1, const Segment &s2) { return (ccw(s1.a, s1.b, s2.a) * ccw(s1.a, s1.b, s2.b) <= 0 && ccw(s2.a, s2.b, s1.a) * ccw(s2.a, s2.b, s1.b) <= 0); }
// 線分sと点pの場合(distance_sp,containsでverify)
bool is_intersect_sp(const Segment &s, const Point &p) { return ccw(s.a, s.b, p) == ON_SEGMENT; }
// 直線lと点pの場合(absが1でない<=>ccwがONLINE_BACKかONLINE_FRONTかON_SEGMENT)(未verify)
bool is_intersect_lp(const Line &l, const Point &p) {
    int res = ccw(l.a, l.b, p);
    return (res == ONLINE_BACK || res == ONLINE_FRONT || res == ON_SEGMENT);
}
// 直線l1,l2の場合(未verify)
bool is_intersect_ll(const Line &l1, const Line &l2) {
    // cross_point_llの説明を参考にしてください
    Point base = l1.b - l1.a;
    Double d12 = cross(base, l2.b - l2.a);
    Double d1 = cross(base, l1.b - l2.a);
    if (sign(d12) == 0 && sign(d1) == 0) return true;  // 一致
    // 平行か1点で交わるか
    return !is_parallel(l1, l2);
}

// 円と円
// 接戦の本数を返す(0は一方がもう一方の内部にある,1~3が交差,4は共にもう一方の外部にある)
int is_intersect_cc(Circle c1, Circle c2) {
    if (c1.r < c2.r) swap(c1, c2);
    Double d = abs(c1.o - c2.o);
    if (c1.r + c2.r < d) return 4;
    if (equals(c1.r + c2.r, d)) return 3;
    if (c1.r - c2.r < d) return 2;
    if (equals(c1.r - c2.r, d)) return 1;
    return 0;
}
// 円と点
bool is_intersect_cp(const Circle &c, const Point &p) { return equals(abs(p - c.o), c.r); }

// 線分の交点(cross point):CGL_2_C
// 2直線l1,l2の交点を求める(未verify)
Point cross_point_ll(const Line &l1, const Line &l2) {
    // 2直線の関係:1点で交わるor平行or一致
    Point base = l1.b - l1.a;
    Double d12 = cross(base, l2.b - l2.a);
    Double d1 = cross(base, l1.b - l2.a);
    // 一致(sign(d12) == 0 は is_parallelと本質的に同じ, sign(d1) == 0は重なっているか)
    if (sign(d12) == 0 && sign(d1) == 0) return l2.a;  // 2直線が一致するので適当に点を返す
    assert(is_parallel(l1, l2) == false);              // assert(sign(d12) != 0);と同じ
    return l2.a + (l2.b - l2.a) * (d1 / d12);
}
// 2線分s1,s2の交点を求める
Point cross_point_ss(const Segment &s1, const Segment &s2) {
    assert(is_intersect_ss(s1, s2));  // 交点を持つかまず判定する
    // 1点で交わるor無数の点で交わる
    Point base = s1.b - s1.a;
    Double d12 = cross(base, s2.b - s2.a);
    Double d1 = cross(base, s1.b - s2.a);
    if (sign(d12) == 0 && sign(d1) == 0) {
        // 無数の点で交わる場合はそのうち1つの点を返す(未verify)
        if (is_intersect_sp(s1, s2.a)) return s2.a;
        if (is_intersect_sp(s1, s2.b)) return s2.b;
        if (is_intersect_sp(s2, s1.a)) return s1.a;
        assert(is_intersect_sp(s2, s1.b));
        return s1.b;
    }
    return s2.a + (s2.b - s2.a) * (d1 / d12);
}

// 距離(distance):CGL_2_D
// 2点a,bの距離を求める(未verify)
Double distance_pp(const Point &a, const Point &b) { return abs(a - b); }
// 直線lと点pの距離を求める(未verify)
Double distance_lp(const Line &l, const Point &p) { return distance_pp(p, projection(l, p)); }
// 線分sと点pの距離を求める
Double distance_sp(const Segment &s, const Point &p) {
    Point r = projection(s, p);
    if (is_intersect_sp(s, r)) return distance_pp(r, p);
    return min(distance_pp(s.a, p), distance_pp(s.b, p));
}
// 線分s1,s2の距離を求める
Double distance_ss(const Segment &s1, const Segment &s2) {
    if (is_intersect_ss(s1, s2)) return 0.0;
    return min({distance_sp(s1, s2.a), distance_sp(s1, s2.b), distance_sp(s2, s1.a), distance_sp(s2, s1.b)});
}

// 多角形
using Polygon = vector<Point>;
// 面積(area):CGL_3_A
// 多角形の面積を外積を用いて求める
Double area(const Polygon &p) {
    int n = (int)p.size();
    assert(n >= 3);
    Double ret = 0;
    for (int i = 0; i < n - 1; i++) {
        ret += cross(p[i], p[i + 1]);
    }
    ret += cross(p[n - 1], p[0]);
    // 点が反時計回りに並んでいた場合はret>0で、時計回りに並んでいた場合はret<0
    return abs(ret) / 2;
}
// 凸性判定(is-convex):CGL_3_B
// 多角形の(広義の)凸性判定を行う(任意の内角が180度「以内」)
// 反時計回り・時計回りどちらも動作する(はず)
// 多角形の辺は共有する端点のみで交差することを仮定(すなわち、ccwの戻り値にONLINE_BACKとON_SEGMENTはない)
// ちなみに上記の仮定を入れるとCGL_3_Bが通らない(テストケースに不備がある)
bool is_convex_polygon(const Polygon &p) {
    int n = (int)p.size();
    assert(n >= 3);
    bool okccw = true, okcw = true;
    for (int i = 0; i < n; i++) {
        int res = ccw(p[i], p[(i + 1) % n], p[(i + 2) % n]);
        assert(res != ONLINE_BACK);
        assert(res != ON_SEGMENT);
        if (res == CLOCKWISE) okccw = false;         // res != COUNTER_CLOCKWISE && res != ONLINE_FRONT
        if (res == COUNTER_CLOCKWISE) okcw = false;  // res != CLOCKWISE && res != ONLINE_FRONT
        if (okccw == false && okcw == false) return false;
    }
    return true;
}
// 多角形-点の包含(polygon-point containment):CGL_3_C
// 点が多角形(凸とは限らない)に含まれるか判定する
// 点を端点としてx軸の正の方向の半直線を考え、何回多角形の線分と交差するかで判定する
constexpr int IN = 2;   // 多角形内
constexpr int ON = 1;   // 多角形の周上
constexpr int OUT = 0;  // 多角形外
int contains(const Polygon &Q, const Point &p) {
    bool x = false;
    int n = (int)Q.size();
    for (int i = 0; i < n; i++) {
        if (is_intersect_sp(Segment(Q[i], Q[(i + 1) % n]), p)) return ON;
        Point a = Q[i] - p, b = Q[(i + 1) % n] - p;
        if (a.imag() > b.imag()) swap(a, b);
        // 半直線が線分の端点と交差する場合などを考えると下記の式が良い(ref:螺旋本)
        if (sign(a.imag()) <= 0 && sign(b.imag()) > 0 && sign(cross(a, b)) > 0) x = !x;
        // うしライブラリは sign(cross(a, b)) < 0 で判定している
    }
    return (x ? IN : OUT);
}
