#include <iostream>
#include <vector>

std::vector<std::vector<int>> edges;
std::vector<int> mark;

void dfs(int u) {
    mark[u] = 1;
    for (int v: edges[u]) {
        if (mark[v] == 0) {
            dfs(v);
        } else if (mark[v] == 1) {
            std::cout << "NO";
            exit(0);
        }
    }
    mark[u] = 2;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        edges.emplace_back();
        mark.emplace_back();
    }
    int u, v;
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < n - i; ++j) {
            char c;
            std::cin >> c;
            if (c == 'R') {
                edges[i + j].emplace_back(i - 1);
            } else {
                edges[i - 1].emplace_back(i + j);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if (mark[i] == 0) {
            dfs(i);
        }
    }
    std::cout << "YES";
}
