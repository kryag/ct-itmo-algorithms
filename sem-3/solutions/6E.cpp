#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int INFINITY = 1'000'000'000;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> d(n, vector<int>(n, INFINITY));
    for (int i = 0; i < n; i++) {
        d[i][i] = 0;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int val;
            cin >> val;
            if (val) {
                d[i][j] = min(d[i][j], val);
            }
        }
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
            cout << (d[i][j] < INFINITY / 2) << " ";
        }
        cout << '\n';
    }
}
