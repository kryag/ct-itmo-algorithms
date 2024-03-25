#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int INFINITY = INT32_MAX;

vector<vector<int>> Floyd(vector<vector<int>>& d, int k) {
    int n = (int) d.size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        }
    }

    return d;
}

template <typename T>
void print_vector(vector<T> const& v) {
    for (auto const& x: v) {
        cout << x << " ";
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> d(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> d[i][j];
        }
    }

    vector<int> remove_nodes(n);
    for (int i = 0; i < n; i++) {
        cin >> remove_nodes[i];
        remove_nodes[i]--;
    }

    vector<long long> result(n);
    vector<bool> mark(n);
    for (int x = n - 1; x >= 0; x--) {
        int rm = remove_nodes[x];
        mark[rm] = true;
        Floyd(d, rm);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (mark[i] && mark[j]) {
                    result[x] += d[i][j];
                }
            }
        }
    }

    print_vector(result);
}
