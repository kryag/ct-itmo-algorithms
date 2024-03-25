#include <algorithm>
#include <iostream>
#include <vector>

struct node {
    std::vector<int> edges;
    std::vector<int> reverse_edges;
};

std::vector<node> graph;
std::vector<int> order;
std::vector<bool> mark;
int count;

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
    ++count;
    for (int v: graph[u].reverse_edges) {
        if (!mark[v]) {
            reverse_dfs(v);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m, u, v;
    std::cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        graph.emplace_back();
        mark.emplace_back();
    }
    for (int i = 0; i < m; ++i) {
        std::cin >> u >> v;
        if (u == v) continue;
        --u; --v;
        graph[v].edges.emplace_back(u);
        graph[u].reverse_edges.emplace_back(v);
    }

    for (int i = 0; i < n; ++i) {
        if (!mark[i]) {
            dfs(i);
        }
    }

    std::reverse(order.begin(), order.end());
    std::fill(mark.begin(), mark.end(), false);

    int res = 0;
    for (int i: order) {
        if (!mark[i]) {
            ++res;
            count = 0;
            reverse_dfs(i);
            res += count > 1;
        }
    }

    std::cout << res << '\n';
}
