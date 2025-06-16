#include <iostream>
#include <vector>
using namespace std;

struct Point {
    int idx, x, y;
    bool used = false;
};

long long signed_area(long long ax, long long ay, long long bx, long long by, long long cx, long long cy) {
    return (bx - ax) * (cy - ay) - (by - ay) * (cx - ax);
}

long long dist_squared(int x1, int y1, int x2, int y2) {
    return (long long)(x1 - x2) * (x1 - x2) + (long long)(y1 - y2) * (y1 - y2);
}

// signed_area를 사용해서 반시계방향 각도가 더 작은지 판단
bool is_smaller_ccw_angle(int base_dx, int base_dy, int dx1, int dy1, int dx2, int dy2,
                          int cur_x, int cur_y, const Point& p1, const Point& p2) {

    // 기준 벡터에서 목표 벡터로의 반시계방향 회전 각도 비교
    long long area1 = signed_area(0, 0, base_dx, base_dy, dx1, dy1);
    long long area2 = signed_area(0, 0, base_dx, base_dy, dx2, dy2);

    // 반시계방향 각도만 고려 (0도 ~ 360도)
    // area > 0: 반시계방향 (0도 ~ 180도)
    // area < 0: 시계방향이지만 반시계방향으로는 (180도 ~ 360도)
    // area = 0: 같은 직선상

    if (area1 == 0 && area2 == 0) {
        // 둘 다 같은 직선상
        long long dot1 = (long long)base_dx * dx1 + (long long)base_dy * dy1;
        long long dot2 = (long long)base_dx * dx2 + (long long)base_dy * dy2;

        if (dot1 > 0 && dot2 > 0) {
            // 둘 다 같은 방향 (0도)
            return dist_squared(cur_x, cur_y, p1.x, p1.y) < dist_squared(cur_x, cur_y, p2.x, p2.y);
        } else if (dot1 > 0) {
            return true; // p1이 0도
        } else if (dot2 > 0) {
            return false; // p2가 0도
        } else {
            // 둘 다 반대 방향 (180도)
            return dist_squared(cur_x, cur_y, p1.x, p1.y) < dist_squared(cur_x, cur_y, p2.x, p2.y);
        }
    }

    if (area1 == 0) {
        long long dot1 = (long long)base_dx * dx1 + (long long)base_dy * dy1;
        if (dot1 > 0) return true; // p1이 0도
        // p1이 180도인 경우, area2 > 0이면 p2가 더 작음
        return area2 <= 0;
    }

    if (area2 == 0) {
        long long dot2 = (long long)base_dx * dx2 + (long long)base_dy * dy2;
        if (dot2 > 0) return false; // p2가 0도
        // p2가 180도인 경우, area1 > 0이면 p1이 더 작음
        return area1 > 0;
    }

    // 둘 다 0이 아닌 경우
    if (area1 > 0 && area2 > 0) {
        // 둘 다 반시계방향 (0도 ~ 180도)
        long long between = signed_area(0, 0, dx1, dy1, dx2, dy2);
        if (between == 0) {
            return dist_squared(cur_x, cur_y, p1.x, p1.y) < dist_squared(cur_x, cur_y, p2.x, p2.y);
        }
        return between > 0; // dx1이 dx2보다 반시계방향에 있으면 더 작은 각도
    }

    if (area1 < 0 && area2 < 0) {
        // 둘 다 시계방향이지만 반시계방향으로는 (180도 ~ 360도)
        long long between = signed_area(0, 0, dx1, dy1, dx2, dy2);
        if (between == 0) {
            return dist_squared(cur_x, cur_y, p1.x, p1.y) < dist_squared(cur_x, cur_y, p2.x, p2.y);
        }
        return between > 0; // dx1이 dx2보다 반시계방향에 있으면 더 작은 각도
    }

    // 하나는 반시계방향, 하나는 시계방향
    return area1 > 0; // 반시계방향(0도~180도)이 더 작은 각도
}

int main() {
    int n;
    cin >> n;

    vector<Point> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].idx >> points[i].x >> points[i].y;
    }

    vector<int> result;
    int cur_x = 0, cur_y = 0;
    int base_dx = 1, base_dy = 0;

    for (int step = 0; step < n; step++) {
        int next = -1;

        for (int i = 0; i < n; i++) {
            if (points[i].used) continue;

            if (next == -1) {
                next = i;
            } else {
                int dx1 = points[next].x - cur_x;
                int dy1 = points[next].y - cur_y;
                int dx2 = points[i].x - cur_x;
                int dy2 = points[i].y - cur_y;

                if (is_smaller_ccw_angle(base_dx, base_dy, dx1, dy1, dx2, dy2,
                                         cur_x, cur_y, points[next], points[i])) {
                    // next가 더 작은 각도, 그대로 유지
                } else {
                    next = i;
                }
            }
        }

        points[next].used = true;
        result.push_back(points[next].idx);

        base_dx = points[next].x - cur_x;
        base_dy = points[next].y - cur_y;
        cur_x = points[next].x;
        cur_y = points[next].y;
    }

    for (int idx : result) {
        cout << idx << "\n";
    }

    return 0;
}