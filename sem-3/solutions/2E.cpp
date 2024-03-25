#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

struct node {
    int x{}, y{}, comp{-1}, index_if_east{-1};
    std::vector<int> edges;
    std::vector<int> reverse_edges;
};

struct SCC {
    int deg{};
    std::pair<int, int> up{INT32_MIN, -1}, down{INT32_MAX, -1};
    std::vector<int> edges;
};

std::vector<SCC> SCC_graph;
std::vector<node> graph;
std::vector<int> order;
std::vector<bool> mark;
int A, B;

bool is_west(int i) {
    return graph[i].x == 0;
}

bool is_east(int i) {
    return graph[i].x == A;
}

void dfs(int u) {
    mark[u] = true;
    for (int v: graph[u].edges) {
        if (!mark[v]) {
            dfs(v);
        }
    }
    order.emplace_back(u);
}

void reverse_dfs(int u, int comp) {
    mark[u] = true;
    graph[u].comp = comp;
    if (is_east(u)) {
        if (SCC_graph[comp].up.first < graph[u].y) {
            SCC_graph[comp].up.first = graph[u].y;
            SCC_graph[comp].up.second = graph[u].index_if_east;
        }
        if (SCC_graph[comp].down.first > graph[u].y) {
            SCC_graph[comp].down.first = graph[u].y;
            SCC_graph[comp].down.second = graph[u].index_if_east;
        }
    }
    for (int v: graph[u].reverse_edges) {
        if (!mark[v]) {
            reverse_dfs(v, comp);
        }
    }
}

bool cmp(int i1, int i2) {
    return graph[i1].y < graph[i2].y;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m, u, v, type;
    std::cin >> n >> m >> A >> B;

    graph.resize(n);
    mark.resize(n);

    std::vector<int> west_nodes;
    std::vector<int> east_nodes;

    for (int i = 0; i < n; ++i) {
        std::cin >> graph[i].x >> graph[i].y;
        if (is_west(i)) {
            west_nodes.emplace_back(i);
        }
    }

    for (int i = 0; i < m; ++i) {
        std::cin >> u >> v >> type;
        --u; --v;
        graph[u].edges.emplace_back(v);
        graph[v].reverse_edges.emplace_back(u);
        if (type == 2) {
            graph[v].edges.emplace_back(u);
            graph[u].reverse_edges.emplace_back(v);
        }
    }

    for (int i: west_nodes) {
        if (!mark[i]) {
            dfs(i);
        }
    }

    for (int i = 0; i < n; ++i) {
        if (is_east(i) && mark[i]) {
            east_nodes.emplace_back(i);
        }
    }

    sort(west_nodes.begin(), west_nodes.end(), cmp);
    sort(east_nodes.begin(), east_nodes.end(), cmp);
    for (int i = 0; i < east_nodes.size(); ++i) {
        graph[east_nodes[i]].index_if_east = i;
    }

    std::reverse(order.begin(), order.end());
    std::fill(mark.begin(), mark.end(), false);

    int comp = -1;
    for (int i: order) {
        if (!mark[i]) {
            ++comp;
            SCC_graph.emplace_back();
            reverse_dfs(i, comp);
        }
    }

    for (int i = 0; i < n; ++i) {
        if (graph[i].comp == -1) continue;
        for (int j: graph[i].edges) {
            if (graph[i].comp != graph[j].comp) {
                SCC_graph[graph[i].comp].edges.emplace_back(graph[j].comp);
                ++SCC_graph[graph[j].comp].deg;
            }
        }
    }

    std::queue<int> q;
    std::vector<int> SCC_order;
    for (int i = 0; i <= comp; ++i) {
        if (!SCC_graph[i].deg) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        v = q.front();
        SCC_order.emplace_back(v);
        q.pop();
        for (int i: SCC_graph[v].edges) {
            if (!--SCC_graph[i].deg) {
                q.push(i);
            }
        }
    }

    for (auto i = SCC_order.rbegin(); i != SCC_order.rend(); ++i) {
        for (int j: SCC_graph[*i].edges) {
            if (SCC_graph[*i].up.first < SCC_graph[j].up.first) {
                SCC_graph[*i].up = SCC_graph[j].up;
            }
            if (SCC_graph[*i].down.first > SCC_graph[j].down.first) {
                SCC_graph[*i].down = SCC_graph[j].down;
            }
        }
    }

    int down, up;
    for (auto i = west_nodes.rbegin(); i != west_nodes.rend(); ++i) {
        down = SCC_graph[graph[*i].comp].down.second;
        up = SCC_graph[graph[*i].comp].up.second;
        if (up == -1 && down == -1) {
            std::cout << 0 << '\n';
            continue;
        }
        std::cout << up - down + 1 << '\n';
    }
}
