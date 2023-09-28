#include <iostream>
#include <algorithm>

const int N = 200'010;
const int countLayers = 19;

int S[N], a[countLayers][N], b[countLayers][N], n;

void build() {
    for (int i = 1; i <= S[n]; ++i) {
        for (int j = 1; j <= n - (1 << i) + 1; ++j) {
            a[i][j] = std::max(a[i - 1][j], a[i - 1][j + (1 << (i - 1))]);
            b[i][j] = std::min(b[i - 1][j], b[i - 1][j + (1 << (i - 1))]);
        }
    }
}

int getA(int l, int r) {
    return std::max(a[S[r - l + 1]][l], a[S[r - l + 1]][r - (1 << S[r - l + 1]) + 1]);
}

int getB(int l, int r) {
    return std::min(b[S[r - l + 1]][l], b[S[r - l + 1]][r - (1 << S[r - l + 1]) + 1]);
}

int binarySearchRight(int border) {
    int l = 0, r = border + 1;
    while (l < r - 1) {
        int mid = (l + r) >> 1;
        if (getA(mid, border) < getB(mid, border)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    return r;
}

int binarySearchLeft(int border) {
    int l = 0, r = border + 1;
    while (l < r - 1) {
        int mid = (l + r) >> 1;
        if (getA(mid, border) > getB(mid, border)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    return r;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> n;
    S[1] = 0;
    for (int i = 2; i <= n; ++i) {
        S[i] = 1 + S[i >> 1];
    }
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[0][i];
    }
    for (int i = 1; i <= n; ++i) {
        std::cin >> b[0][i];
    }
    long long ans = 0;
    build();
    for (int i = 1; i <= n; ++i) {
        ans += (binarySearchRight(i) - binarySearchLeft(i));
    }
    std::cout << ans << '\n';
    return 0;
}
