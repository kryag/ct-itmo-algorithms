#include <algorithm>
#include <iostream>
#include <vector>

std::vector<std::vector<int>> edges;
std::vector<int> from;
std::vector<int> mark;

void dfs(int u, int p) {
    mark[u] = true;
    from[u] = p;
    for (int v: edges[u]) {
        if (mark[v] == 0) {
            dfs(v, u);
        } else if (mark[v] == 1) {
            std::vector<int> res;
            int count = 0;
            while (u != v) {
                res.emplace_back(u);
                ++count;
                u = from[u];
            }
            res.emplace_back(v);
            ++count;
            std::cout << count << '\n';
            for (auto i = res.rbegin(); i != res.rend(); ++i) {
                std::cout << *i + 1 << " ";
            }
            exit(0);
        }
    }
    mark[u] = 2;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n, m, i;
    std::cin >> n >> m;
    for (i = 0; i < n; ++i) {
        edges.emplace_back();
        from.emplace_back(-1);
        mark.emplace_back();
    }
    int u, v;
    for (i = 0; i < m; ++i) {
        std::cin >> u >> v;
        edges[u - 1].emplace_back(v - 1);
    }
    for (i = 0; i < n; ++i) {
        if (mark[i] == 0) {
            dfs(i, -1);
        }
    }
    std::cout << -1;
}
