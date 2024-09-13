//
// Created by Aleksandr Kiriak on 17.05.2024.
//
#include <bits/stdc++.h>

using namespace std;

const int INF = INT32_MAX;

int n;
vector<vector<int>> C;

pair<int, vector<int>> hungarian() {
    vector<int> u(n + 1), v(n + 1), match(n + 1), path(n + 1);

    for (int i = 1; i <= n; i++) {
        vector<int> min_v(n + 1, INF);
        vector<bool> mark(n + 1, false);
        match[0] = i;
        int cur_col = 0;

        do {
            int cur_row = match[cur_col], rem = INF, min_col = 0;
            mark[cur_col] = true;
            for (int j = 1; j <= n; j++) {
                if (mark[j]) {
                    continue;
                }
                int cur = C[cur_row][j] - u[cur_row] - v[j];
                if (cur < min_v[j]) {
                    path[j] = cur_col;
                    min_v[j] = cur;
                }
                if (min_v[j] < rem) {
                    min_col = j;
                    rem = min_v[j];
                }
            }
            for (int j = 0; j <= n; j++) {
                if (mark[j]) {
                    v[j] -= rem;
                    u[match[j]] += rem;
                } else {
                    min_v[j] -= rem;
                }
            }
            cur_col = min_col;
        } while (match[cur_col] != 0);

        do {
            int min_col = path[cur_col];
            match[cur_col] = match[min_col], cur_col = min_col;
        } while (cur_col != 0);
    }

    vector<int> answer(n + 1);
    for (int j = 1; j <= n; j++) {
        answer[match[j]] = j;
    }

    return {-v[0], answer};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;

    C.resize(n + 1, vector<int>(n + 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> C[i + 1][j + 1];
        }
    }

    pair<int, vector<int>> answer = hungarian();
    cout << answer.first << endl;
    for (int i = 1; i <= n; i++) {
        cout << i << ' ' << answer.second[i] << endl;
    }
}
