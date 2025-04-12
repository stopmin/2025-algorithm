#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    int sum_xy = 0, square_xy = 0, x, count = 0;
    while (cin >> x) {
        sum_xy += x;
        square_xy += x * x;
        count++;
    }

    int total_sum = N * (N + 1) / 2;
    int total_square = N * (N + 1) * (2 * N + 1) / 6;
    int remaining_sum = total_sum - sum_xy;
    int remaining_square = total_square - square_xy;

    if (count == N - 1) cout << remaining_sum << "\n";
    else {
        int xy = (remaining_sum * remaining_sum - remaining_square) / 2;
        int discriminant = remaining_sum * remaining_sum - 4 * xy;
        int root = (int)sqrt(discriminant);
        int a = (remaining_sum - root) / 2;
        int b = (remaining_sum + root) / 2;
        cout << min(a, b) <<"\n"<< max(a, b);
    }
}
