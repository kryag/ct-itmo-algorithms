#include <iostream>
#include <vector>

struct edge {
    int from, to, id;
    bool is_fake;

    edge(int from, int to, int id, bool is_fake) {
        this->from = from;
        this->to = to;
        this->id = id;
        this->is_fake = is_fake;
    }
};

struct node {
    int deg{};
    std::vector<edge> edges;
};

std::vector<node> graph;
std::vector<bool> mark;
std::vector<edge> euler_cycle;

void add_edge(edge const& e) {
    graph[e.from].edges.emplace_back(e);
    ++graph[e.from].deg;
    graph[e.to].edges.emplace_back(e.to, e.from, e.id, e.is_fake);
    ++graph[e.to].deg;
}

void euler(int v, int p = -1, bool is_fake = false) {
    while (!graph[v].edges.empty()) {
        auto const e = graph[v].edges.back();
        graph[v].edges.pop_back();
        if (mark[e.id]) continue;
        mark[e.id] = true;
        euler(e.to, v, e.is_fake);
    }
    if (p != -1) {
        euler_cycle.emplace_back(v, p, 0, is_fake);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m, v, u;
    std::cin >> n >> m;
    graph.resize(n);

    for (int i = 0; i < m; ++i) {
        std::cin >> v >> u;
        --v; --u;
        add_edge({v, u, i, false});
    }

    int count_simple_path = 0, prev = -1, id = m;
    for (int i = 0; i < n; ++i) {
        if (graph[i].deg % 2 == 1) {
            if (++count_simple_path % 2 == 1) {
                prev = i;
            } else {
                add_edge({prev, i, id++, true});
            }
        }
    }

    mark.resize(id);
    euler(0);

    count_simple_path /= 2;
    std::cout << std::max(count_simple_path, 1) << '\n';

    if (!count_simple_path) {
        std::cout << euler_cycle[0].from + 1 << " ";
        for (edge const& e: euler_cycle) {
            std::cout << e.to + 1 << " ";
        }
        return 0;
    }

    std::vector<std::vector<int>> paths(count_simple_path + 1);
    int count = 0;
    for (edge const& e: euler_cycle) {
        paths[count].emplace_back(e.from);
        if (e.is_fake) ++count;
    }
    for (int i: paths.back()) {
        std::cout << i + 1 << " ";
    }
    for (int i = 0; i < paths.size() - 1; ++i) {
        for (int j: paths[i]) {
            std::cout << j + 1 << " ";
        }
        std::cout << '\n';
    }
}
