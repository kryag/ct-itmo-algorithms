#include <iostream>
#include <vector>
#include <set>

struct edge {
    int from, to, id;

    edge(int from, int to, int id) {
        this->from = from;
        this->to = to;
        this->id = id;
    }
};

struct node {
    int deg{};
    std::vector<edge> edges;
};

std::vector<node> graph;
std::vector<bool> mark;
std::vector<edge> euler_cycle;

void euler(int v, int p = -1) {
    while (!graph[v].edges.empty()) {
        auto const e = graph[v].edges.back();
        graph[v].edges.pop_back();
        if (mark[e.id]) continue;
        mark[e.id] = true;
        euler(e.to, v);
    }
    if (p != -1) {
        euler_cycle.emplace_back(v, p, 0);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    graph.resize(n);

    int m, to, len, edge_id = 0;
    for (int i = 0; i < n; ++i) {
        std::cin >> m;
        for (int j = 0; j < m; ++j) {
            std::cin >> to >> len;
            --to;
            if (to < i) continue;
            graph[i].edges.emplace_back(i, to, edge_id);
            graph[to].edges.emplace_back(to, i, edge_id++);
            ++graph[i].deg;
            ++graph[to].deg;
        }
    }

    int start = 0;
    for (int i = 0; i < n; ++i) {
        if (graph[i].deg % 2 == 1) {
            start = i;
        }
    }

    mark.resize(edge_id);
    euler(start);

    std::cout << euler_cycle.size() << '\n';
    std::cout << euler_cycle[0].from + 1 << " ";
    for (edge const& e: euler_cycle) {
        std::cout << e.to + 1 << " ";
    }
}
