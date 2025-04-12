#include <iostream>
#include <cmath>
using namespace std;
#define ll long long

int main() {
    ll N, x; cin >> N;

    ll sum = N * (N + 1) / 2;
    ll sqSum = N * (N + 1) * (2 * N + 1) / 6;

    while (cin >> x) {
        sum -= x;
        sqSum -= x * x;
        N--;
    }

    if (N == 1) {
        cout << sum << "\n";
    } else {
        ll xy = (sum * sum - sqSum) / 2;
        ll d = sqrt(sum * sum - 4 * xy);

        ll a = (sum - d) / 2;
        ll b = (sum + d) / 2;

        cout << a << "\n" << b << "\n";
    }
}