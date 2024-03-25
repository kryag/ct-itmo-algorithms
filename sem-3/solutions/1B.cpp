#include <iostream>
#include <vector>

struct node {
    int n;
    std::vector<int> edges;

    explicit node(int n) {
        this->n = n;
    }
};

struct component {
    int size{};
    std::vector<int> nodes;
};

std::vector<node> graph;
std::vector<component> components;
std::vector<bool> mark;

void dfs(int u) {
    mark[u] = true;
    ++components.back().size;
    components.back().nodes.emplace_back(u);
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
            components.emplace_back();
            dfs(i);
        }
    }
    std::cout << components.size() << '\n';
    for (component const& c : components) {
        std::cout << c.size << '\n';
        for (int i : c.nodes) {
            std::cout << (i + 1) << " ";
        }
        std::cout << '\n';
    }
}
