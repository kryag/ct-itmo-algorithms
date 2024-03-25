#include <iostream>
#include <vector>
#include <map>

using namespace std;

typedef pair<int, int> edge;

struct node {
    int c{};
    vector<int> edges;
};

vector<node> graph;
map<edge, bool> orientation; // 0 = ->, 1 = <-

void add_orientation(int a, int b, bool orient) {
    orientation[{a, b}] = orient;
    orientation[{b, a}] = !orient;
}

void dfs_cycle(int v, int start) {
    if (v == start) return;
    for (int u: graph[v].edges) {
        if (!orientation.count({u, v}) && graph[u].c == graph[v].c) {
            add_orientation(v, u, false);
            dfs_cycle(u, start);
        }
    }
}

void dfs(int v) {
    for (int u: graph[v].edges) {
        if (!orientation.count({u, v})) {
            if (graph[v].c >= graph[u].c) {
                add_orientation(v, u, false);
            } else {
                add_orientation(v, u, true);
            }
            if (graph[v].c == graph[u].c) {
                dfs_cycle(u, v);
            }
            dfs(u);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    graph.resize(n);

    vector<edge> q_edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        q_edges.emplace_back(u, v);
        graph[u].edges.push_back(v);
        graph[v].edges.push_back(u);
    }
    for (int i = 0; i < n; i++) {
        cin >> graph[i].c;
    }

    for (int i = 0; i < n; i++) {
        dfs(i);
    }

    for (auto const& e: q_edges) {
        cout << (orientation[e] ? "<-" : "->") << '\n';
    }
}
