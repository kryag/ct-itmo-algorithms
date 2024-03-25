#include <algorithm>
#include <iostream>
#include <vector>

struct node {
    int i, SCC;
    std::vector<int> edges;
    std::vector<int> reverse_edges;

    explicit node(int i) {
        this->i = i;
        SCC = 0;
    }

    void add_edge(node& to) {
        edges.emplace_back(to.i);
        to.reverse_edges.emplace_back(i);
    }
};

int n, SCC;
std::vector<node> graph;
std::vector<int> order;
std::vector<bool> mark;

void dfs(int u) {
    mark[u] = true;
    for (int v: graph[u].edges) {
        if (!mark[v]) {
            dfs(v);
        }
    }
    order.emplace_back(u);
}

void reverse_dfs(int u) {
    mark[u] = true;
    graph[u].SCC = SCC;
    for (int v: graph[u].reverse_edges) {
        if (!mark[v]) {
            reverse_dfs(v);
        }
    }
}

void SCC_top_sort() {
    for (int i = 0; i < 2 * n; ++i) {
        mark.emplace_back();
    }

    for (int i = 0; i < 2 * n; ++i) {
        if (!mark[i]) {
            dfs(i);
        }
    }

    std::reverse(order.begin(), order.end());
    std::fill(mark.begin(), mark.end(), false);

    SCC = 0;
    for (int i: order) {
        if (!mark[i]) {
            ++SCC;
            reverse_dfs(i);
        }
    }
}

void clear() {
    graph.clear();
    mark.clear();
    order.clear();
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int m, i1, i2;
    bool e1, e2;

    while (std::cin >> n >> m) {
        clear();
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < n; ++j) {
                graph.emplace_back(j + i * n);
            }
        }
        while (m--) {
            std::cin >> i1 >> e1 >> i2 >> e2;
            graph[i1 + (e1 ? n : 0)].add_edge(graph[i2 + (e2 ? 0 : n)]);
            graph[i2 + (e2 ? n : 0)].add_edge(graph[i1 + (e1 ? 0 : n)]);
        }

        SCC_top_sort();
        for (int i = 0; i < n; ++i) {
            std::cout << (graph[i].SCC > graph[i + n].SCC);
        }
        std::cout << '\n';
    }
}
