#include <bits/stdc++.h>
using namespace std;
using task = pair<int, int>;

int N, T, K;
vector<task> taskList, primarySet, backupSet;
int maxProfit = 0, secondProfit = 0;
int dayAssigned[11], deadlineCount[11];

bool check_schedulable() {
    int overflow = 0;
    for (int d = T; d >= 1; --d) {
        overflow += deadlineCount[d] - K;
        if (overflow < 0) overflow = 0;
    }
    return overflow == 0;
}

void find_first_best() {
    for (task t: taskList) {
        bool done = false;
        for (int d = t.second; d >= 1; --d) {
            if (dayAssigned[d] < K) {
                dayAssigned[d]++;
                deadlineCount[d]++;
                primarySet.push_back(t);
                maxProfit += t.first;
                done = true;
                break;
            }
        }
        if (!done) backupSet.push_back(t);
    }
    cout<<maxProfit<<" ";
}

void find_second_best() {
    // 1. 하나 빼고 아무것도 안 넣는(test case 2번에서 너무 틀ㄹ미 ㅠㅠㅠㅠㅠ)
    for (int i = 0; i < primarySet.size(); ++i) {
        task removed = primarySet[i];
        deadlineCount[removed.second]--;

        if (check_schedulable()) {
            int profit = maxProfit - removed.first;
            secondProfit = max(secondProfit, profit);
        }

        deadlineCount[removed.second]++;
    }

    // 2. 하나 빼고 다른 거 넣는
    for (task selected : primarySet) {
        for (task candidate : backupSet) {
            if (selected == candidate) continue;

            deadlineCount[selected.second]--;
            deadlineCount[candidate.second]++;

            if (check_schedulable()) {
                int profit = maxProfit - selected.first + candidate.first;
                if (profit < maxProfit)
                    secondProfit = max(secondProfit, profit);
            }

            deadlineCount[selected.second]++;
            deadlineCount[candidate.second]--;
        }
    }
    cout<<secondProfit;
}

int main() {
    cin >> N >> T >> K;
    taskList.resize(N);
    for (int i = 0; i < N; ++i)
        cin >> taskList[i].first >> taskList[i].second;

    sort(taskList.begin(), taskList.end(), [](task a, task b){return a.first > b.first;});
    find_first_best();
    cout<<" ";
    find_second_best();
}