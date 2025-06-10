#include "bits/stdc++.h"
#define MAX_N 70
using namespace std;

using Coord = pair<int, int>;

int N, M;
array<Coord, MAX_N> coords;
array<vector<Coord>, MAX_N> graph;
array<bool, MAX_N> visited;

vector<int> best_path;
int best_edge_count = 0;
int best_max_weight = INT_MAX;

void update(const vector<int>& path, const vector<int>& weights) {
    int edge_count = path.size() - 1;
    int max_weight = *max_element(weights.begin(), weights.end());

    if (best_edge_count == 0 ||
        edge_count > best_edge_count ||
        (edge_count == best_edge_count &&
         (max_weight < best_max_weight ||
          (max_weight == best_max_weight && path < best_path)))) {
        best_edge_count = edge_count;
        best_path = path;
        best_max_weight = max_weight;
    }
}

void dfs(int curr, int dist, vector<int>& path, vector<int>& weights) {
    for (auto [next, w] : graph[curr]) {
        if (next == 0) {
            if (path.size() >= 2 && dist + w == 42) {
                path.push_back(0);
                weights.push_back(w);
                update(path, weights);
                path.pop_back();
                weights.pop_back();
            }
        } else if (!visited[next] && dist + w < 42) {
            visited[next] = true;
            path.push_back(next);
            weights.push_back(w);
            dfs(next, dist + w, path, weights);
            path.pop_back();
            weights.pop_back();
            visited[next] = false;
        }
    }
}

int main() {
    cin >> N;
    for (int i = 0; i < N; ++i) {
        int idx, x, y;
        cin >> idx >> x >> y;
        coords[idx] = {x, y};
    }

    cin >> M;
    for (int i = 0; i < M; ++i) {
        int edge_id, u, v;
        cin >> edge_id >> u >> v;
        int dx = coords[u].first - coords[v].first;
        int dy = coords[u].second - coords[v].second;
        int d = static_cast<int>(floor(sqrt(dx * dx + dy * dy)));
        graph[u].push_back({v, d});
        graph[v].push_back({u, d});
    }

    for (int i = 0; i < N; ++i)
        sort(graph[i].begin(), graph[i].end());

    visited.fill(false);
    visited[0] = true;
    vector<int> path = {0};
    vector<int> weights;
    dfs(0, 0, path, weights);

    if (best_edge_count == 0) {
        cout << -1;
    } else {
        for (int i = 0; i < best_path.size(); ++i) {
            if (i) cout << " ";
            cout << best_path[i];
        }
    }
}