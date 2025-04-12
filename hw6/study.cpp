#include <bits/stdc++.h>
using namespace std;
int n, k;
int nums[100] = {0,};

bool isValid(int k, int maxSum) {
    int count = 1;
    int currentSum = 0;
    for (int i = 0; i < n; i++) {
        if (currentSum + nums[i] > maxSum) {
            count++;
            currentSum = nums[i];
            if (count > k) return false;
        } else {
            currentSum += nums[i];
        }

    }
    return true;
}

int splitArray(int k) {
    int left = *max_element(nums, nums + n);
    int right = accumulate(nums, nums + n, 0);
    while (left < right) {
        int mid = (left + right) / 2;
        if (isValid(k, mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

int main() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) cin >> nums[i];
    cout << splitArray(k);
}