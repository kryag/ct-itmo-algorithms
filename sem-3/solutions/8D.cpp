#include <iostream>
#include <vector>

using namespace std;

vector<int> z_function(string const& s) {
    int n = (int) s.length();
    vector<int> z(n);
    int l = 0;
    for (int i = 1; i < n; i++) {
        z[i] = max(0, min(z[i - l], z[l] + l - i));
        while (i + z[i] < n && s[z[i]] == s[z[i] + i]) {
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

    string s1, s2;
    cin >> s1 >> s2;

    auto p = z_function(s1 + '#' + s2 + s2);
    for (int i = 0; i < p.size(); i++) {
        if (p[i] >= s1.size()) {
            cout << i - s1.size() - 1 << '\n';
            return 0;
        }
    }
    cout << -1 << '\n';
}
