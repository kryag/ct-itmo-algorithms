#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int DELIMITER = INT32_MIN;

vector<int> z_function(vector<int> const& v) {
    int n = (int) v.size();
    vector<int> z(n);
    int l = 0;
    for (int i = 1; i < n; i++) {
        z[i] = max(0, min(z[i - l], z[l] + l - i));
        while (i + z[i] < n && v[z[i]] == v[z[i] + i]) {
            z[i]++;
        }
        if (i + z[i] > l + z[l]) {
            l = i;
        }
    }
    return z;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> a(2 * n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i + n] = a[i];
    }

    vector<int> b(k);
    for (int i = 0; i < k; i++) {
        cin >> b[i];
    }

    if (k > n) {
        return 0;
    }

    if (k == 1) {
        for (int i = 0; i < n; i++) {
            cout << i + 1 << " ";
        }
        cout << '\n';
        return 0;
    }

    vector<int> ab;
    for (int i = 1; i < k; i++) {
        ab.push_back(b[i] - b[i - 1]);
    }
    ab.push_back(DELIMITER);
    for (int i = 1; i < 2 * n; i++) {
        ab.push_back(a[i] - a[i - 1]);
    }

    auto z = z_function(ab);
    for (int i = k; i <= k + n - 1; i++) {
        if (z[i] == k - 1) {
            cout << i - k + 1 << " ";
        }
    }
    cout << '\n';
}
