#include <iostream>
#include <vector>
#include <queue>

struct node {
    int deg{};
    std::vector<int> edges;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<node> graph(n);
    int u, v;
    for (int i = 0; i < m; ++i) {
        std::cin >> u >> v;
        graph[u - 1].edges.emplace_back(v - 1);
        ++graph[v - 1].deg;
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> u;
        --u;
        if (graph[u].deg != 0) {
            std::cout << "NO";
            return 0;
        }
        for (int e: graph[u].edges) {
            --graph[e].deg;
        }
    }
    std::cout << "YES";
}
