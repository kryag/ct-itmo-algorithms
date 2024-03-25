#include <iostream>
#include <vector>

struct node {
    int color{};
    std::vector<int> edges;
};

std::vector<node> graph;
std::vector<bool> mark;

void dfs(int u, int color) {
    mark[u] = true;
    graph[u].color = color;
    for (int v: graph[u].edges) {
        if (!mark[v]) {
            dfs(v, color == 1 ? 2 : 1);
        } else if (graph[v].color == color) {
            std::cout << -1;
            exit(0);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        graph.emplace_back();
        mark.emplace_back();
    }
    int u, v;
    for (int i = 0; i < m; ++i) {
        std::cin >> u >> v;
        graph[u - 1].edges.emplace_back(v - 1);
        graph[v - 1].edges.emplace_back(u - 1);
    }
    for (int i = 0; i < n; ++i) {
        if (!mark[i]) {
            dfs(i, 1);
        }
    }
    for (int i = 0; i < n; ++i) {
        std::cout << graph[i].color << " ";
    }
}
