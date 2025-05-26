#include "bits/stdc++.h"
#define MAX_M 21
using namespace std;

int k;
int mp, mf, ms, mv;
struct ingredient {
    int p, f, s, v, c; // 단백질, 지방, 탄수화물, 비타민, 비용
};
ingredient ingredients[MAX_M];

int bestCost = INT_MAX;
int bestSum = -1;
vector<int> bestSelected;

// 백트래킹
void dfs(int idx, vector<int>& selected, int tp, int tf, int ts, int tv, int cost) {
    if (idx == k) {
        // 조건 만족 + 최적 갱신 여부 판단
        if(tp >= mp && tf >= mf && ts >= ms && tv >= mv){
            int total = tp + tf + ts + tv;

            if (cost < bestCost ||
                (cost == bestCost && total > bestSum) ||
                (cost == bestCost && total == bestSum && selected < bestSelected)) {
                bestCost = cost;
                bestSum = total;
                bestSelected = selected;
            }
        }
        return;
    }

    // 현재 재료 선택 x
    dfs(idx + 1, selected, tp, tf, ts, tv, cost);

    // 현재 재료 선택 d
    selected.push_back(idx);
    dfs(idx + 1, selected,
        tp + ingredients[idx].p,
        tf + ingredients[idx].f,
        ts + ingredients[idx].s,
        tv + ingredients[idx].v,
        cost + ingredients[idx].c);
    selected.pop_back();
}

int main() {
    cin >> k; // 식재료의 개수
    cin >> mp >> mf >> ms >> mv; // 최소 권장량

    for (int i = 0; i < k; ++i) cin >> ingredients[i].p >> ingredients[i].f >> ingredients[i].s >> ingredients[i].v >> ingredients[i].c;

    vector<int> selected;
    dfs(0, selected, 0, 0, 0, 0, 0);

    if(bestCost == INT_MAX){
        cout<<0;
    }
    else{
        for (int i = 0; i < bestSelected.size(); ++i) cout<<bestSelected[i] + 1 << " ";
    }
}