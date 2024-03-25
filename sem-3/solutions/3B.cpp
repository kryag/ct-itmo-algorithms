#include <iostream>
#include <vector>
#include <set>

struct node {
    int depth{}, up{};
    std::vector<int> edges;
};

std::vector<node> graph;
std::vector<bool> mark;
std::set<int> ans;

void dfs(int v, int p = -1, int depth = 0) {
    graph[v].depth = graph[v].up = depth;
    mark[v] = true;
    int count_children = 0;
    for (int u: graph[v].edges) {
        if (u == p) continue;
        if (!mark[u]) {
            dfs(u, v, depth + 1);
            graph[v].up = std::min(graph[v].up, graph[u].up);
            if (graph[u].up >= graph[v].depth && p != -1) {
                ans.insert(v);
            }
            ++count_children;
        } else {
            graph[v].up = std::min(graph[v].up, graph[u].depth);
        }
    }
    if (count_children > 1 && p == -1) {
        ans.insert(v);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

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
    }

    for (int i = 0; i < n; ++i) {
        if (!mark[i]) {
            dfs(i);
        }
    }

    std::cout << ans.size() << '\n';
    for (int p: ans) {
        std::cout << p + 1 << " ";
    }
}
