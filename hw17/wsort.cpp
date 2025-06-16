#include <iostream>
#include <vector>

using namespace std;

struct Point {
    int id, x, y;
};

int signed_area(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int dist2(Point a, Point b) {
    int dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}

int main() {
    int n;
    cin >> n;
    vector<Point> pt(n);
    for (auto &p: pt) cin >> p.id >> p.x >> p.y;

    vector<bool> used(n);
    Point cur = {0, 0, 0}, base = {0, -1, 0};

    for (int t = 0; t < n; ++t) {
        int sel = -1;
        for (int i = 0; i < n; ++i) {
            if (used[i]) continue;
            if (sel == -1) {
                sel = i;
                continue;
            }
            Point a = pt[sel], b = pt[i];
            int sa = signed_area(base, cur, a), sb = signed_area(base, cur, b);
            if (sa < 0 && sb >= 0) {
                sel = i;
                continue;
            }
            if (sa >= 0 && sb < 0) continue;

            int ang = signed_area(cur, a, b);
            if (ang < 0) sel = i;
            else if (ang == 0 && dist2(cur, b) < dist2(cur, a)) sel = i;
        }
        cout << pt[sel].id << '\n';
        used[sel] = true;
        base = cur;
        cur = pt[sel];
    }
}