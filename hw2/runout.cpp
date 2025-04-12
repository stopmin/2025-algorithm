#include <bits/stdc++.h>

#define MAX_VALUE 5001
#define ROW 0
#define COLUMN 1
using namespace std;

int N, M;
int runway[MAX_VALUE][MAX_VALUE], dp_row[MAX_VALUE][MAX_VALUE], dp_col[MAX_VALUE][MAX_VALUE];

struct ans {
    int x, y, w;
};

ans dp(int dir) {
    ans res = {0, 0, 0}; // 결과값 초기화

    if (dir == ROW) { // 가로 방향 처리
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (runway[i][j] == 0) {
                    dp_row[i][j] = (j == 0 ? 1 : dp_row[i][j - 1] + 1);

                    if (i > 0 && runway[i - 1][j] == 0) {
                        int w = min(dp_row[i][j], dp_row[i - 1][j]);
                        int x = j + 1;
                        int y = N - i + 1;

                        if (w > res.w || (w == res.w && make_pair(x - (w - 1), y) < make_pair(res.x, res.y))) {
                            res = {x - (w - 1), y, w};
                        }
                    }
                }
            }
        }
    } else { // 세로 방향 처리
        for (int j = 0; j < M; j++) {
            for (int i = 0; i < N; i++) {
                if (runway[i][j] == 0) {
                    dp_col[i][j] = (i == 0 ? 1 : dp_col[i - 1][j] + 1);

                    if (j > 0 && runway[i][j - 1] == 0) {
                        int w = min(dp_col[i][j], dp_col[i][j - 1]);

                        int x = j;
                        int y = N - i;
                        if (w > res.w || (w == res.w && make_pair(x , y + (w - 1)) < make_pair(res.x, res.y))) {
                            res = {x, y + (w - 1), w};
                        }
                    }
                }
            }
        }
    }

    return res;
}

int main() {
    cin >> N >> M;

    for (int i = 0; i < N; i++) {
        string row;
        cin >> row;
        for (int j = 0; j < M; j++) {
            runway[i][j] = row[j] - '0';
        }
    }

    ans rowAns = dp(ROW);
    ans colAns = dp(COLUMN);

    if (rowAns.w > colAns.w || (rowAns.w == colAns.w && make_pair(rowAns.x, rowAns.y) < make_pair(colAns.x, colAns.y))) {
        cout << rowAns.x << " " << rowAns.y << " " << rowAns.w << "\n";
    } else {
        cout << colAns.x << " " << colAns.y << " " << colAns.w << "\n";
    }
}