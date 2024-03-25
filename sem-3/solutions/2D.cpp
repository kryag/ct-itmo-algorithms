#include <algorithm>
#include <iostream>
#include <vector>

struct node {
    int comp{};
    std::vector<std::pair<int, bool>> edges;
    std::vector<std::pair<int, bool>> reverse_edges;
};

std::vector<node> graph;
std::vector<int> order;
std::vector<bool> reachable;
std::vector<bool> mark;

void dfs1(int u) {
    reachable[u] = true;
    for (auto const& v: graph[u].edges) {
        if (!reachable[v.first]) {
            dfs1(v.first);
        }
    }
}

void dfs2(int u) {
    mark[u] = true;
    for (auto const& v: graph[u].edges) {
        if (!v.second) continue;
        if (!mark[v.first]) {
            dfs2(v.first);
        }
    }
    order.emplace_back(u);
}

void reverse_dfs(int u, int comp) {
    mark[u] = true;
    graph[u].comp = comp;
    for (auto const& v: graph[u].reverse_edges) {
        if (!v.second) continue;
        if (!mark[v.first]) {
            reverse_dfs(v.first, comp);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m, u, v, t;
    std::cin >> n >> m;

    graph.resize(n);
    mark.resize(n);
    reachable.resize(n);

    for (int i = 0; i < m; ++i) {
        std::cin >> u >> v >> t;
        --u; --v, --t;
        graph[u].edges.emplace_back(v, t);
        graph[v].reverse_edges.emplace_back(u, t);
    }

    dfs1(0);
    for (int i = 0; i < n; ++i) {
        if (reachable[i] && !mark[i]) {
            dfs2(i);
        }
    }

    std::reverse(order.begin(), order.end());
    std::fill(mark.begin(), mark.end(), false);

    int comp = 0;
    for (int i: order) {
        if (!mark[i]) {
            ++comp;
            reverse_dfs(i, comp);
        }
    }

    for (int i: order) {
        for (auto const& j: graph[i].edges) {
            if (graph[i].comp == graph[j.first].comp) continue;
            if (j.second) {
                std::cout << "YES";
                return 0;
            }
        }
    }
    std::cout << "NO";
}
