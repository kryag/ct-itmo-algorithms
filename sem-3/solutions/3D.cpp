#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

const int MOD = 1'000'000'007;

struct node {
    int depth{}, up{}, cmp{};
    std::vector<int> edges;
};

struct class_eq {
    int count_nodes{}, deg{};
    std::vector<int> edges;
};

std::vector<class_eq> DLC;
std::vector<node> graph;
std::vector<bool> mark;
std::stack<int> st;
long long ways = 1;
int count_cmp, count_leaf;

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
            graph[u].cmp = count_cmp;
        }
        ++count_cmp;
    }
}

void dfs_DLC(int u) {
    mark[u] = true;
    if (!DLC[u].deg || DLC[u].deg == 1) {
        ++count_leaf;
        ways = (ways * DLC[u].count_nodes) % MOD;
    }
    for (int v: DLC[u].edges) {
        if (!mark[v]) {
            dfs_DLC(v);
        }
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
                graph[u].cmp = count_cmp;
            }
            ++count_cmp;
        }
    }

    DLC.resize(count_cmp);
    for (int i = 0; i < n; ++i) {
        ++DLC[graph[i].cmp].count_nodes;
        for (int to: graph[i].edges) {
            if (i > to) continue;
            if (graph[to].cmp != graph[i].cmp) {
                DLC[graph[i].cmp].edges.emplace_back(graph[to].cmp);
                DLC[graph[to].cmp].edges.emplace_back(graph[i].cmp);
                ++DLC[graph[i].cmp].deg;
                ++DLC[graph[to].cmp].deg;
            }
        }
    }

    fill(mark.begin(), mark.end(), false);
    dfs_DLC(0);

    std::cout << count_leaf << " " << ways;
}
