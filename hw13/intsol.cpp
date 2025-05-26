#include "bits/stdc++.h"

#define MOD 11111
#define MAX_R 10000
#define MAX_N 11
using namespace std;
int n, R, sum_c = 0; // n:변수 개수, R: 양의 변수 범위
int dp[MAX_R] = {0,}; // i가 될 수 있는 경우의 합임.
int c[MAX_N] = {0,};

int solve() {
    int target = R - sum_c;

    dp[0] = 1; // 그냥 1
    for (int i = 0; i < n; ++i) {
        for (int j = c[i]; j <= target; ++j) {
            // j를 만드는 방법의 수는 j - c[i]원을 만든 다음 거기에 c[i]를 한번 더 쓰면 됨.
            // 즉 8을 만드는 모든 방법에 4를 붙이면 12를 만들 수 있음.
            dp[j] = (dp[j] + dp[j - c[i]]) % MOD;
        }
    }

    return dp[target];
}

int main() {
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> c[i];
        sum_c += c[i];
    }
    cin >> R;

    cout << solve();
}