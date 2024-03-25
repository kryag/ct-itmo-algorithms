#include <iostream>
#include <vector>

struct node {
    int n;
    std::vector<int> edges;

    explicit node(int n) {
        this->n = n;
    }
};

std::vector<node> graph;
std::vector<bool> mark;

void dfs(int u) {
    mark[u] = true;
    for (int v: graph[u].edges) {
        if (!mark[v]) {
            std::cout << (u + 1) << " " << (v + 1) << '\n';
            dfs(v);
        }
    }
}

int main() {
    int n, m, u, v;
    std::cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        graph.emplace_back(i);
        mark.emplace_back();
    }
    for (int i = 0; i < m; ++i) {
        std::cin >> u >> v;
        graph[u - 1].edges.emplace_back(v - 1);
        graph[v - 1].edges.emplace_back(u - 1);
    }
    dfs(0);
}
