#include <algorithm>
#include <iostream>
#include <vector>

struct node {
    int cmp = -1;
    std::vector<int> edges;
};

std::vector<node> graph;
std::vector<node> reverse_graph;
std::vector<int> order;
std::vector<bool> mark;
int n, cur_cmp;

int inverse(int i) {
    return i < n ? i + n : i - n;
}

void add_edge(int v, int u) {
    graph[v].edges.emplace_back(u);
    reverse_graph[u].edges.emplace_back(v);
    graph[inverse(u)].edges.emplace_back(inverse(v));
    reverse_graph[inverse(v)].edges.emplace_back(inverse(u));
}

void dfs(int v) {
    mark[v] = true;
    for (int u: graph[v].edges) {
        if (!mark[u]) {
            dfs(u);
        }
    }
    order.emplace_back(v);
}

void reverse_dfs(int v) {
    mark[v] = true;
    reverse_graph[v].cmp = cur_cmp;
    for (int u: reverse_graph[v].edges) {
        if (!mark[u]) {
            reverse_dfs(u);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int m;
    std::cin >> n >> m;

    graph.resize(n * 2);
    reverse_graph.resize(n * 2);

    std::vector<int> p(n), q(n), reverse_p(n), reverse_pq(n);
    std::vector<std::pair<int, int>> ban(m);
    for (int i = 0; i < n; ++i) {
        std::cin >> p[i];
        --p[i];
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> q[i];
        --q[i];
    }
    for (int i = 0; i < n; ++i) {
        reverse_p[p[i]] = i;
        reverse_pq[q[p[i]]] = i;
    }
    for (int i = 0; i < m; ++i) {
        std::cin >> ban[i].first >> ban[i].second;
        --ban[i].first, --ban[i].second;
    }

    for (int i = 0; i < n; ++i) {
        if (reverse_pq[i] != reverse_p[i]) {
            add_edge(reverse_p[i], reverse_pq[i]);
        }
    }
    for (int i = 0; i < m; ++i) {
        for (int e1 = 0; e1 < 2; ++e1) {
            for (int e2 = 0; e2 < 2; ++e2) {
                int f1 = e1 ? reverse_pq[ban[i].first] : reverse_p[ban[i].first];
                int f2 = e2 ? reverse_pq[ban[i].second] : reverse_p[ban[i].second];
                if (abs(f1 - f2) <= 1) {
                    add_edge(f1 + e1 * n, inverse(f2 + e2 * n));
                }
            }
        }
    }

    mark.resize(n * 2);
    for (int i = 0; i < n * 2; ++i) {
        if (!mark[i]) {
            dfs(i);
        }
    }
    std::fill(mark.begin(), mark.end(), false);
    for (auto i = order.rbegin(); i != order.rend(); ++i) {
        if (!mark[*i]) {
            reverse_dfs(*i);
            ++cur_cmp;
        }
    }

    for (int i = 0; i < n; ++i) {
        if (reverse_graph[i].cmp == reverse_graph[i + n].cmp) {
            std::cout << "-1";
            return 0;
        }
    }
    for (int i = 0; i < n; ++i) {
        std::cout << (reverse_graph[i].cmp > reverse_graph[i + n].cmp ? "1" : "2") << " ";
    }
}
