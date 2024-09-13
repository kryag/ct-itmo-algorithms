//
// Created by Aleksandr Kiriak on 21.05.2024.
//
#include <iostream>
#include <cstdint>
#include <vector>

using namespace std;

const int INF = INT32_MAX;

int n;
vector<vector<int>> C;

vector<int> hungarian() {
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

    return answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;

    vector<int> p(2 * n);
    vector<pair<int, int>> no(n, {-1, -1});
    for (int i = 0; i < 2 * n; i++) {
        cin >> p[i];
        int index = p[i] - 1;
        if (no[index].first == -1) {
            no[index].first = i;
        } else {
            no[index].second = i;
        }
    }

    C.resize(n + 1, vector<int>(n + 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i + 1][j + 1] = abs(j - no[i].first) + abs(j + n - no[i].second);
        }
    }

    vector<int> answer = hungarian();
    vector<int> result(2 * n);
    for (int i = 0; i < n; i++) {
        int pos = answer[i + 1];
        result[pos - 1] = i + 1;
        result[pos - 1 + n] = i + 1;
    }

    for (int i = 0; i < 2 * n; i++) {
        cout << result[i] << " ";
    }
    cout << endl;
}
