#include<bits/stdc++.h>
using namespace std;

struct Vec {
    double x, y, z;
    Vec operator-(const Vec v) const { return {x - v.x, y - v.y, z - v.z}; }
    Vec operator+(const Vec v) const { return {x + v.x, y + v.y, z + v.z}; }
    Vec operator*(double k) const { return {x * k, y * k, z * k}; }
    double norm() const { return sqrt(x * x + y * y + z * z); }
};

double dist(Vec a, Vec b) {
    return (a - b).norm();
}

double min_distance(Vec A, Vec B, Vec C, Vec D) {
    auto get = [&](Vec p) {
        double l = 0, r = 1;
        for (int i = 0; i < 100; i++) {
            double s1 = (2*l + r)/3, s2 = (l + 2*r)/3;
            Vec q1 = C + (D - C) * s1;
            Vec q2 = C + (D - C) * s2;
            if (dist(p, q1) < dist(p, q2)) r = s2;
            else l = s1;
        }
        Vec q = C + (D - C) * ((l + r)/2);
        return dist(p, q);
    };

    double l = 0, r = 1, res = 1e18;
    for (int i = 0; i < 100; i++) {
        double t1 = (2*l + r)/3, t2 = (l + 2*r)/3;
        Vec p1 = A + (B - A) * t1;
        Vec p2 = A + (B - A) * t2;
        double d1 = get(p1), d2 = get(p2);
        if (d1 < d2) r = t2, res = min(res, d1);
        else l = t1, res = min(res, d2);
    }
    return res;
}

int main() {
    Vec P[4];
    for (int i = 0; i < 4; i++) cin >> P[i].x >> P[i].y >> P[i].z;
    cout << (int)ceil(min_distance(P[0], P[1], P[2], P[3]));
}