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
int n;

void dfs(int v, int p = -1, int depth = 0) {
    graph[v].depth = graph[v].up = depth;
    mark[v] = true;
    int count_children = 0;
    for (int u: graph[v].edges) {
        if (u == p) continue;
        if (!mark[u]) {
            dfs(u, v, depth + 1);
            graph[v].up = std::min(graph[v].up, graph[u].up);
            if (graph[u].up >= graph[v].depth && p != -1 && v >= n) {
                ans.insert(v);
            }
            ++count_children;
        } else {
            graph[v].up = std::min(graph[v].up, graph[u].depth);
        }
    }
    if (count_children > 1 && p == -1 && v >= n) {
        ans.insert(v);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int m, v[3];
    std::cin >> n >> m;

    graph.resize(n + m);
    mark.resize(n + m);
    for (int i = 0; i < m; ++i) {
        for (int &j: v) {
            std::cin >> j;
            --j;
            graph[n + i].edges.emplace_back(j);
            graph[j].edges.emplace_back(n + i);
        }
    }

    for (int i = 0; i < n; ++i) {
        if (!mark[i]) {
            dfs(i);
        }
    }

    std::cout << ans.size() << '\n';
    for (int a: ans) {
        std::cout << a + 1 - n << " ";
    }
}
