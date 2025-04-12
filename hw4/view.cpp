#include <bits/stdc++.h>

using namespace std;

int main() {
    int N;
    cin >> N;
    pair<char, int> building[21];

    for (int i = 0; i < N; i++) cin >> building[i].first >> building[i].second;

    int mountain = 0;
    for (int i = 0; i < N-1; i++) {
        if (building[i].second > mountain) {
            cout << building[i].first<<" ";
            mountain = building[i].second;
        }
    }
    cout<<'\n';

    int sea = 0;
    stack<char> s;
    for (int i = N-1; i >= 0; i--) {
        if (building[i].second > sea) {
            s.push(building[i].first);
            sea = building[i].second;
        }
    }
    while(!s.empty()){
        cout<<s.top()<<" ";
        s.pop();
    }
}