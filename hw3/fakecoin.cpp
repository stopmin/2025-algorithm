#include "fakecoin.h"
#define RIGHT_IS_LIGHT 1
#define LEFT_IS_LIGHT -1
#define THE_OTHER_IS_LIGHT 0
void find_light(int low, int size) { // 크기, 시작점
    int mid = low + size / 3, high = low + size / 3 * 2;
    int low_and_mid_size = size / 3, high_size = size - low_and_mid_size * 2;
    if (size == 2) {
        low_and_mid_size = 1, high_size = 0;
        mid = low + 1;
    }

    memset(left, 0, sizeof(left));
    memset(right, 0, sizeof(right));

    for (int i = low; i < low+low_and_mid_size; i++) left[i] = 1;
    for (int i = mid; i < mid+low_and_mid_size; i++) right[i] = 1;

    int result = balance(left, right);
    if (result == THE_OTHER_IS_LIGHT) {
        if (high_size == 1) report_coin(high);
        else find_light(high, high_size);
    } else if (result == RIGHT_IS_LIGHT) {
        if (low_and_mid_size == 1) report_coin(mid);
        else find_light(mid, low_and_mid_size);
    } else if (result == LEFT_IS_LIGHT) {
        if (low_and_mid_size == 1) report_coin(low);
        else find_light(low, low_and_mid_size);
    }
}


int main() {
    load_coins();
    find_light(1, 21);
}