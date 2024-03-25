#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int INFINITY = INT32_MAX;
const int NO_EDGE = 100'000;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n;

    vector<vector<int>> d(n, vector<int>(n, INFINITY));
    for (int i = 0; i < n; i++) {
        d[i][i] = 0;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int weight;
            cin >> weight;
            if (weight == NO_EDGE) {
                continue;
            }
            d[i][j] = min(d[i][j], weight);
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (d[i][k] != INFINITY && d[k][j] != INFINITY) {
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (d[i][i] < 0) {
            cout << "YES" << '\n';
            return 0;
        }
    }
    cout << "NO" << '\n';
}
