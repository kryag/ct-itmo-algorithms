#include <iostream>
#include <vector>
#include <set>

struct node {
    int depth{}, up{};
    std::vector<int> edges;
};

std::vector<node> graph;
std::vector<bool> mark;
std::set<std::pair<int, int>> bridges;

void dfs(int v, int p = -1, int depth = 0) {
    graph[v].depth = depth;
    graph[v].up = depth;
    mark[v] = true;
    bool flag = false;
    for (int u: graph[v].edges) {
        if (u == p && !flag) {
            flag = true;
            continue;
        }
        if (!mark[u]) {
            dfs(u, v, depth + 1);
            graph[v].up = std::min(graph[v].up, graph[u].up);
        } else {
            graph[v].up = std::min(graph[v].up, graph[u].depth);
        }
    }
    if (graph[v].up == graph[v].depth && p != -1) {
        bridges.insert(std::make_pair(p, v));
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::vector<std::pair<int, int>> edges;
    int n, m, v, u;
    std::cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        graph.emplace_back();
        mark.emplace_back();
    }
    for (int i = 0; i < m; ++i) {
        std::cin >> v >> u;
        --v; --u;
        graph[v].edges.emplace_back(u);
        graph[u].edges.emplace_back(v);
        edges.emplace_back(v, u);
    }

    for (int i = 0; i < n; ++i) {
        if (!mark[i]) {
            dfs(i);
        }
    }

    std::cout << bridges.size() << '\n';
    for (int i = 0; i < edges.size(); ++i) {
        if (bridges.count(edges[i]) || bridges.count(std::make_pair(edges[i].second, edges[i].first))) {
            std::cout << i + 1 << " ";
        }
    }
}
