//
// Created by Aleksandr Kiriak on 17.05.2024.
//
#include <bits/stdc++.h>

using namespace std;

const int INF = INT32_MAX;

string encrypted_note, correct_answers;
vector<vector<int>> weight;
vector<int> match_L, match_R;
vector<int> part_L, part_R;
vector<bool> mark_L, mark_R;
int dist, K;

bool dfs(int v) {
    mark_L[v] = true;
    for (int y = 0; y < K; y++) {
        if (mark_R[y]) {
            continue;
        }
        if (part_L[v] + part_R[y] != weight[v][y]) {
            dist = min(dist, part_L[v] + part_R[y] - weight[v][y]);
            continue;
        }
        mark_R[y] = true;
        if (match_R[y] == -1 || dfs(match_R[y])) {
            match_L[v] = y;
            match_R[y] = v;
            return true;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    cin >> N >> K;
    cin >> encrypted_note >> correct_answers;

    weight.resize(K, vector<int>(K));
    match_L.resize(K, -1);
    match_R.resize(K, -1);
    part_L.resize(K);
    part_R.resize(K);
    mark_L.resize(K);
    mark_R.resize(K);

    auto calc = [](char c) {
        return c >= 'a' ? c - 'a' : c - 'A' + 26;
    };
    for (int i = 0; i < N; i++) {
        weight[calc(encrypted_note[i])][calc(correct_answers[i])]++;
    }

    for (int v = 0; v < K; v++) {
        for (int u = 0; u < K; u++) {
            part_L[v] = max(part_L[v], weight[v][u]);
        }
    }

    int v = 0;
    while (v < K) {
        fill(mark_L.begin(), mark_L.end(), false);
        fill(mark_R.begin(), mark_R.end(), false);
        dist = INF;
        if (dfs(v)) {
            v++;
            continue;
        }
        for (int u = 0; u < K; u++) {
            if (mark_L[u]) {
                part_L[u] -= dist;
            }
            if (mark_R[u]) {
                part_R[u] += dist;
            }
        }
    }

    int answer = 0;
    for (int u = 0; u < K; u++) {
        answer += weight[u][match_L[u]];
    }

    cout << answer << endl;
    for (int u = 0; u < K; u++) {
        int x = match_L[u];
        cout << (x < 26 ? char(x + 'a') : char(x + 'A' - 26));
    }
    cout << endl;
}
