#include <bits/stdc++.h>
#define INF 1e9

using namespace std;
using geocode = pair<int, int>;

int distance(const geocode &a, const geocode &b) {
    int dx = a.first - b.first;
    int dy = a.second - b.second;
    return (int) sqrt(1LL * dx * dx + 1LL * dy * dy);
}

int main() {
    int N; cin >> N;

    vector<geocode> points(N);
    for (int i = 0; i < N; ++i) {
        cin >> points[i].first >> points[i].second;
    }
    points.push_back({0, 500});

    // sorting
    sort(points.begin(), points.end());

    int n = points.size();
    vector<vector<int>> dp(n, vector<int>(n, INF));

    // (0,500) -> 첫 번째 통발
    dp[0][1] = distance(points[0], points[1]);

    for (int j = 2; j < n; ++j) {
        for (int i = 0; i < j - 1; ++i) {
            dp[i][j] = dp[i][j - 1] + distance(points[j - 1], points[j]);
        }
        int best = INF;
        for (int k = 0; k < j - 1; ++k) {
            best = min(best, dp[k][j - 1] + distance(points[k], points[j]));
        }
        dp[j - 1][j] = best;
    }

    int answer = dp[n - 2][n - 1] + distance(points[n - 2], points[n - 1]);
    cout << answer;
}