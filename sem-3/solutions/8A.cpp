#include <iostream>
#include <vector>

using namespace std;

vector<int> prefix_function(string const& s) {
    int n = (int) s.length();
    vector<int> p(n);
    p[0] = 0;
    for (int i = 1; i < n; i++) {
        int j = p[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = p[j - 1];
        }
        p[i] = j + (s[i] == s[j]);
    }
    return p;
}

template <typename T>
void print_vector(vector<T> const& v) {
    for (T const& x: v) {
        cout << x << " ";
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string s;
    cin >> s;
    print_vector(prefix_function(s));
}
