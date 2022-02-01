#include "template.cpp"

/**
 * 五芒星を5本の5角形の対角線で表現する
 * 使用例：https://onlinejudge.u-aizu.ac.jp/status/users/ruthen71/submissions/1/2402/judge/6243498/C++14
 */

struct star5 {
    vector<Segment> Segs;
    Double x, y, deg, r;
    star5() {}
    star5(Double x, Double y, Double deg, Double r) : x(x), y(y), deg(deg), r(r) {
        Point a1 = polar(r, PI / 2 + degree_to_radian(deg));
        Point p = Point(x, y);
        for (int i = 0; i < 5; i++) {
            Point a2 = rotate(a1, degree_to_radian(144));
            Segs.push_back(Segment(a1 + p, a2 + p));
            a1 = a2;
        }
    }
};

Double distance_star5(const star5 &s1, const star5 &s2) {
    Double ret = numeric_limits<Double>::infinity();
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            ret = min(ret, distance_ss(s1.Segs[i], s2.Segs[j]));
        }
    }
    return ret;
}
