#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <unordered_map>

struct node {
    int depth{}, up{};
    std::vector<int> edges;
};

std::vector<node> graph;
std::vector<bool> mark;
std::map<std::pair<int, int>, int> map;
std::stack<std::pair<int, int>> st;
int cur_cmp = 1;

void dfs(int v, int p = -1, int depth = 0) {
    mark[v] = true;
    graph[v].up = graph[v].depth = depth;
    for (int u: graph[v].edges) {
        if (u == p) continue;
        if (!mark[u]) {
            st.emplace(v, u);
            dfs(u, v, depth + 1);
            if (graph[u].up >= graph[v].depth) {
                int cmp = cur_cmp++;
                while (st.top() != std::pair(v, u)) {
                    map[st.top()] = cmp;
                    map[std::make_pair(st.top().second, st.top().first)] = cmp;
                    st.pop();
                }
                map[std::make_pair(v, u)] = cmp;
                map[std::make_pair(u, v)] = cmp;
                st.pop();
            }
            if (graph[u].up < graph[v].up) {
                graph[v].up = graph[u].up;
            }
        } else if (graph[u].depth < graph[v].depth) {
            st.emplace(v, u);
            if (graph[u].depth < graph[v].up) {
                graph[v].up = graph[u].depth;
            }
        } else if (graph[v].up > graph[u].depth) {
            graph[v].up = graph[u].up;
        }
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
            if (st.empty()) continue;
            while (!st.empty()) {
                auto e = st.top();
                st.pop();
                map[e] = cur_cmp;
            }
            ++cur_cmp;
        }
    }

    std::cout << cur_cmp - 1 << '\n';
    std::unordered_map<int, int> index_cmp;
    cur_cmp = 1;

    for (auto const& e: edges) {
        if (index_cmp.count(map[e])) {
            std::cout << index_cmp[map[e]] << " ";
        } else if (index_cmp.count(map[std::make_pair(e.second, e.first)])) {
            std::cout << index_cmp[map[std::make_pair(e.second, e.first)]] << " ";
        } else {
            index_cmp[map[e]] = cur_cmp;
            index_cmp[map[std::make_pair(e.second, e.first)]] = cur_cmp;
            std::cout << cur_cmp++ << " ";
        }
    }
}
