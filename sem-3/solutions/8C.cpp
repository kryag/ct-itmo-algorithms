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

    string s, t;
    cin >> s >> t;

    vector<int> z = z_function(t + '#' + s);
    for (int i = (int) t.size() + 1; i <= s.size() + 1; i++) {
        if (z[i] == (int) t.size()) {
            cout << i - t.size() - 1 << " ";
        }
    }
    cout << '\n';
}
