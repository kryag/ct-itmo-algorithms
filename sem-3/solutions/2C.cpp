#include <algorithm>
#include <iostream>
#include <vector>

const int UNINITIALIZED = -1, CYCLE = -2;

struct node {
    int a{};
    long long dp{};
    std::vector<int> edges;
};

std::vector<node> graph;
bool has_cycle;

long long dfs(int u, int cur_max) {
    if (graph[u].a > cur_max) {
        return 0;
    }
    if (graph[u].dp == CYCLE) {
        has_cycle = true;
        return 0;
    }
    if (graph[u].dp != UNINITIALIZED) {
        return graph[u].dp;
    }
    graph[u].dp = CYCLE;
    long long max_len = 0;
    for (int v: graph[u].edges) {
        max_len = std::max(max_len, dfs(v, cur_max));
    }
    graph[u].dp = max_len + 1;
    return graph[u].dp;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    long long n, m, k;
    int a, max_a, u, v;
    std::cin >> n >> m >> k;
    graph.resize(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a;
        graph[i].a = a;
        max_a = std::max(max_a, a);
    }
    for (int i = 0; i < m; ++i) {
        std::cin >> u >> v;
        graph[u - 1].edges.emplace_back(v - 1);
    }

    int left = 1, right = max_a;

    label:
    while (left <= right) {
        int mid = (left + right) / 2;
        for (int i = 0; i < n; ++i) {
            graph[i].dp = UNINITIALIZED;
        }
        has_cycle = false;
        for (int i = 0; i < n; ++i) {
            if (dfs(i, mid) >= k || has_cycle) {
                right = mid - 1;
                goto label;
            }
        }
        left = mid + 1;
    }

    std::cout << (right == max_a ? -1 : right + 1);
}
