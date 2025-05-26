#include <iostream>
using namespace std;

#define MAX_N 10
#define MAX_DIAG 19

int N, Diag; // N, 대각선

// 목표 카운트
int colTarget[MAX_N], rowTarget[MAX_N], diagRightTarget[MAX_DIAG], diagLeftTarget[MAX_DIAG];

// 현재 카운트
int colCount[MAX_N], rowCount[MAX_N], diagRightCount[MAX_DIAG], diagLeftCount[MAX_DIAG];
int grid[MAX_N][MAX_N];

void inputArray(int* arr, int size) {
    for (int i = 0; i < size; ++i) cin >> arr[i];
}

bool dfs(int row, int col) {
    if (row == N) {
        for (int i = 0; i < N; ++i) if (colCount[i] != colTarget[i] || rowCount[i] != rowTarget[i]) return false;
        for (int i = 0; i < Diag; ++i) if (diagRightCount[i] != diagRightTarget[i] || diagLeftCount[i] != diagLeftTarget[i]) return false;
        return true;
    }

    bool last = col == N - 1;
    int nextRow = last ? row + 1 : row;
    int nextCol = last ? 0 : col + 1;

    // case 0: 안 놓는 경우
    grid[row][col] = 0;
    if (dfs(nextRow, nextCol)) return true;

    // case 1: 놓는 경우
    int diagR = row + col, diagL = row - col + N - 1, remCol = N - row - 1, remRow = N - col - 1;

    int remDiagR = 0, remDiagL = 0;
    for (int i = row + 1; i < N; ++i) {
        int jR = diagR - i, jL = i - diagL + N - 1;
        if (jR >= 0 && jR < N) remDiagR++;
        if (jL >= 0 && jL < N) remDiagL++;
    }

    // 증가
    grid[row][col] = 1;
    colCount[col]++;
    rowCount[row]++;
    diagRightCount[diagR]++;
    diagLeftCount[diagL]++;

    // 가지치기 조건
    if (colCount[col] <= colTarget[col] && colTarget[col] - colCount[col] <= remCol &&
        rowCount[row] <= rowTarget[row] && rowTarget[row] - rowCount[row] <= remRow &&
        diagRightCount[diagR] <= diagRightTarget[diagR] && diagRightTarget[diagR] - diagRightCount[diagR] <= remDiagR &&
        diagLeftCount[diagL] <= diagLeftTarget[diagL] && diagLeftTarget[diagL] - diagLeftCount[diagL] <= remDiagL &&
        dfs(nextRow, nextCol)) return true;

    // backtrack
    grid[row][col] = 0;
    colCount[col]--;
    rowCount[row]--;
    diagRightCount[diagR]--;
    diagLeftCount[diagL]--;

    return false;
}

int main() {
    cin >> N;
    Diag = N * 2 - 1;

    inputArray(colTarget, N);
    inputArray(rowTarget, N);
    inputArray(diagLeftTarget, Diag);
    inputArray(diagRightTarget, Diag);

    dfs(0, 0);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            cout << (grid[i][j] ? 'B' : '-') << ' ';
        cout << '\n';
    }
}

//    for (int i = 0; i < N; ++i) cin >> colTarget[i];
//    for (int i = 0; i < N; ++i) cin >> rowTarget[i];
//    for (int i = 0; i < Diag; ++i) cin >> diagLeftTarget[i];
//    for (int i = 0; i < Diag; ++i) cin >> diagRightTarget[i];