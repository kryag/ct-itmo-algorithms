#include <iostream>
#include <vector>
#include <algorithm>

const int SIZE = 100'001;
std::vector<int> a(SIZE);
int table[SIZE][18];

void create(int n) {
    for (int i = 1; i < n + 1; ++i) {
        table[i][0] = a[i];
    }
    for (int i = 1; (1 << i) < n + 1; ++i) {
        for (int j = 1; 1 << i < n + 2 - j; ++j) {
            table[j][i] = std::min(table[j][i - 1], table[j + (1 << (i - 1))][i - 1]);
        }
    }
}

int find(int lq, int rq) {
    int noLayer = 31 - __builtin_clz(rq - lq);
    return std::min(table[lq][noLayer], table[rq - (1 << noLayer) + 1][noLayer]);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m, u, v;
    a[0] = 0;
    std::cin >> n >> m >> a[1];
    for (int i = 2; i < n + 1; i++) {
        a[i] = (23 * a[i - 1] + 21563) % 16714589;
    }
    create(n);
    std::cin >> u >> v;
    int result = find(u, v);
    for (int i = 2; i < m + 1; i++) {
        u = ((17 * u + 751 + result + 2 * (i - 1)) % n) + 1;
        v = ((13 * v + 593 + result + 5 * (i - 1)) % n) + 1;
        result = (u <= v) ? find(u, v) : find(v, u);
    }
    std::cout << u << " " << v << " " << result;
    return 0;
}
