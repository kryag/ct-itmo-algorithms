#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>

struct node {
    int depth{}, up{}, cmp{};
    std::vector<int> edges;
};

std::vector<node> graph;
std::vector<bool> mark;
std::stack<int> st;
int cur_cmp = 1;

void dfs(int v, int p = -1, int depth = 0) {
    st.push(v);
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
            st.push(v);
            graph[v].up = std::min(graph[v].up, graph[u].up);
        } else {
            graph[v].up = std::min(graph[v].up, graph[u].depth);
        }
    }
    if (graph[v].up == graph[v].depth && p != -1) {
        while (st.top() != p) {
            int u = st.top();
            st.pop();
            graph[u].cmp = cur_cmp;
        }
        ++cur_cmp;
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
            while (!st.empty()) {
                u = st.top();
                st.pop();
                graph[u].cmp = cur_cmp;
            }
            ++cur_cmp;
        }
    }

    std::cout << cur_cmp - 1 << '\n';
    std::unordered_map<int, int> index_cmp; // старое -> новое
    cur_cmp = 1;

    for (auto const& vertex: graph) {
        if (index_cmp.count(vertex.cmp)) {
            std::cout << index_cmp[vertex.cmp] << " ";
        } else {
            index_cmp[vertex.cmp] = cur_cmp;
            std::cout << cur_cmp++ << " ";
        }
    }
}
