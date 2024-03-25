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
std::vector<int> main_nodes;
std::vector<bool> mark;

void dfs(int u) {
    mark[u] = true;
    main_nodes.back() = u;
    for (int v: graph[u].edges) {
        if (!mark[v]) {
            dfs(v);
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
        graph.emplace_back(i);
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
            main_nodes.emplace_back();
            dfs(i);
        }
    }
    std::cout << main_nodes.size() - 1 << '\n';
    for (int i = 0; i < main_nodes.size() - 1; ++i) {
        std::cout << main_nodes[i] + 1 << " " << main_nodes[i + 1] + 1 << '\n';
    }
}
