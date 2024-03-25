#include <iostream>
#include <vector>
#include <queue>

struct node {
    int deg{};
    std::vector<int> edges;
};

std::vector<node> graph;
std::vector<int> mark;

void dfs(int u) {
    mark[u] = 1;
    for (int v: graph[u].edges) {
        if (mark[v] == 0) {
            dfs(v);
        } else if (mark[v] == 1) {
            std::cout << -1;
            exit(0);
        }
    }
    mark[u] = 2;
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
        ++graph[v - 1].deg;
    }
    for (int i = 0; i < n; ++i) {
        if (mark[i] == 0) {
            dfs(i);
        }
    }
    std::queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (!graph[i].deg) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        v = q.front();
        std::cout << v + 1 << " ";
        q.pop();
        for (int i: graph[v].edges) {
            if (!--graph[i].deg) {
                q.push(i);
            }
        }
    }
}
