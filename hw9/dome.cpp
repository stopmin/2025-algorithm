#include <bits/stdc++.h>

#define MAX_SIZE 1001
using namespace std;

int N, M;
int prefix[MAX_SIZE][MAX_SIZE];

// (x1, y1) ~ (x2, y2)의 장애물 개수 반환한다.
int getObstacleCount(int x1, int y1, int x2, int y2) {
    return prefix[x2][y2]
           - prefix[x1 - 1][y2]
           - prefix[x2][y1 - 1]
           + prefix[x1 - 1][y1 - 1];
}

tuple<int, int, int> binary_search() {
    int lo = 1, hi = min(N, M), maxK = 0;
    int ansX = -1, ansY = -1;

    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        bool found = false;
        int curX = -1, curY = -1;

        for (int i = 1; i + mid - 1 <= N; i++) {
            for (int j = 1; j + mid - 1 <= M; j++) {
                int x2 = i + mid - 1;
                int y2 = j + mid - 1;
                int obstacles = getObstacleCount(i, j, x2, y2);

                if (obstacles <= 1) {
                    if (!found || j < curY || (j == curY && i < curX)) {
                        curX = i;
                        curY = j;
                    }
                    found = true;
                }
            }
        }

        if (found) {
            maxK = mid;
            ansX = curX;
            ansY = curY;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }

    return {ansX, ansY, maxK};
}

int main() {
    cin >> N >> M;

    for (int i = 0; i < N; i++) { // 가로로 뒤집기..
        for (int j = 1; j <= M; j++) {
            char c;
            cin >> c;
            prefix[N - i][j] = c - '0';
        }
    }

    // 2D 누적합
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            prefix[i][j] += prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1];
        }
    }

    auto [ansX, ansY, maxK] = binary_search();

    cout << ansY << " " << ansX << '\n';
    cout << maxK;
}