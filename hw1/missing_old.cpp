#include <iostream>
#include <unordered_set>
using namespace std;

int main() {
    int N, x;
    cin >> N;

    unordered_set<int> numbers;
    for (int i = 1; i <= N; i++) numbers.insert(i);

    while(cin >> x){
        numbers.erase(x);
    }

    if (numbers.size() == 1) {
        cout << *numbers.begin();
    } else {
        int a = *numbers.begin();
        int b = *(++numbers.begin());
        if (a > b) swap(a, b);
        cout << a << "\n" << b << "\n";
    }
}