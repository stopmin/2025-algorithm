#include <cstring>
#include "twofakes.h"
#include <bits/stdc++.h>

#define LEFT_IS_HEAVY 1
#define RIGHT_IS_HEAVY (-1)
std::vector<int> ans;

int fill_coin(int start, int end) {
    memset(left, 0, sizeof(left));
    memset(right, 0, sizeof(right));
    int count = end - start + 1;
    int mid = start + count / 2;

    for (int i = start; i < mid; i++) left[i] = 1;
    for (int i = mid; i <= end; i++) right[i] = 1;
    return balance(left, right);
}

void recur(int start, int end, bool wasSame) {
    int count = end - start + 1;
    if (count < 1) return;
    int mid = start + count / 2;
    int result = fill_coin(start, end);

    if (result == LEFT_IS_HEAVY) {
        if (count == 2) {
            ans.push_back(end);
            return;
        }
        recur(mid, end, false);
    } else if (result == RIGHT_IS_HEAVY) {
        if (count == 2) {
            ans.push_back(start);
            return;
        }
        recur(start, mid - 1, false);
    } else {
        if (wasSame && count != 2) {
            return;
        }
        else if (!wasSame && count == 2){
            ans.push_back(start);
            ans.push_back(start+1);
            return;
        }
        recur(start, start + count / 2 - 1, true);
        recur(start+count/2, end, true);
    }
}


int main() {
    load_coins();
    recur(1, 8, false);

    if(ans.size() == 2) two_fakes(ans[0], ans[1]);
    else if(ans.size()==0){
        two_fakes(9, 10);
    }
    else {
        recur(9, 10, false);
        two_fakes(ans[0], ans[1]);
    }
}