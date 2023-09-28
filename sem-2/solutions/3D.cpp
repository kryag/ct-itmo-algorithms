#include <bits/stdc++.h>

const int N = 200005, LOG = 20;
int lg[N];
long long n, sp[LOG][N], a[N];
std::map<int, int> map;

void build() {
    lg[1] = 0;
    for (int i = 2; i <= n; ++i) {
        lg[i] = lg[i / 2] + 1;
    }
    for (int i = 1; i <= n; ++i) {
        sp[0][i] = a[i];
    }
    for (int i = 1; (1 << i) <= n; ++i) {
        for (int j = 1; j + (1 << i) - 1 <= n; ++j) {
            sp[i][j] = (sp[i - 1][j] | sp[i - 1][j + (1 << (i - 1))]);
        }
    }
}

long long get(int l, int r) {
    int temp = lg[r - l + 1];
    return (sp[temp][l] | sp[temp][r - (1 << temp) + 1]);
}

long long binarySearchRight(int l, int r, int index) {
    while (l < r) {
        int m = r - (r - l) / 2;
        if (get(index, m) == a[index]) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    return r;
}

long long binarySearchLeft(int l, int r, int index) {
    while (l < r) {
        int m = (l + r) / 2;
        if (get(m, index) == a[index]) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    return l;
}

long long eliminate(int index) {
    int tmp = 0;
    if (map.count(a[index])) {
        tmp = map[a[index]];
    }
    long long d1 = index - binarySearchLeft(tmp + 1, index, index) + 1;
    long long d2 = binarySearchRight(index, n, index) - index + 1;
    return d1 * d2 - 1;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }
    build();
    long long answer = n * (n - 1) / 2;
    for (int i = 1; i <= n; i++) {
        answer -= eliminate(i);
        map[a[i]] = i;
    }
    std::cout << answer << '\n';
    return 0;
}
