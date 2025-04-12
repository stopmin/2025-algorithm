#include <bits/stdc++.h>
#include "battery.h"
using namespace std;

int binary_search(bool x) {
    int lo = 0, hi = 100000, ans = 0;
    while (lo <= hi) {
        int mid = (lo + hi) / 2; int result;

        if (x) result = experiment(mid, 0);
        else   result = experiment(0, mid);

        if (result == 1) {
            ans = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }

    return ans;
}

int main() {
    ready();
    int cx = binary_search(true);
    int cy = binary_search(false);
    int mymaxE =  (cx + cy) * (cx + cy);
    report_maxE((int)mymaxE);
}