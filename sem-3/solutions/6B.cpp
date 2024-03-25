#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int INFINITY = 1'000'000;
const int NO_PATH = 30'000;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> d(n, vector<int>(n, INFINITY));
    for (int i = 0; i < n; i++) {
        d[i][i] = 0;
    }

    for (int i = 0; i < m; i++) {
        int from, to, weight;
        cin >> from >> to >> weight;
        from--, to--;
        d[from][to] = min(d[from][to], weight);
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (d[i][j] > INFINITY / 2) {
                cout << NO_PATH << " ";
            } else {
                cout << d[i][j] << " ";
            }
        }
        cout << '\n';
    }
}
