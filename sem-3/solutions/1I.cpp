#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

struct node {
    int min_value = INT32_MAX, deg = 0;
    std::vector<std::pair<int, int>> edges;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n, m, s, t;
    std::cin >> n >> m >> s >> t;
    std::vector<node> graph(n);
    --s;
    --t;
    int u, v, w;
    for (int i = 0; i < m; ++i) {
        std::cin >> u >> v >> w;
        graph[u - 1].edges.emplace_back(v - 1, w);
        ++graph[v - 1].deg;
    }
    std::queue<int> q;
    std::vector<int> top_sort;
    for (int i = 0; i < n; ++i) {
        if (!graph[i].deg) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        v = q.front();
        top_sort.emplace_back(v);
        q.pop();
        for (auto const& e: graph[v].edges) {
            if (!--graph[e.first].deg) {
                q.push(e.first);
            }
        }
    }
    auto start = std::find(top_sort.begin(), top_sort.end(), s);
    auto end = std::find(top_sort.begin(), top_sort.end(), t);
    graph[*start].min_value = 0;
    for (; start < end; ++start) {
        if (graph[*start].min_value == INT32_MAX) continue;
        for (auto const& e: graph[*start].edges) {
            graph[e.first].min_value = std::min(graph[e.first].min_value, graph[*start].min_value + e.second);
        }
    }
    if (graph[*end].min_value == INT32_MAX) {
        std::cout << "Unreachable";
        return 0;
    }
    std::cout << graph[*end].min_value;
}
