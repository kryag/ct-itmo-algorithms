#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct DSU {
    vector<int> parent;
    vector<int> rank;

    explicit DSU(int size) {
        parent.resize(size);
        rank.resize(size);
        for (int i = 0; i < size; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int find(int i) {
        if (i == parent[i]) {
            return i;
        }
        return parent[i] = find(parent[i]);
    }

    void connect(int x, int y) {
        x = find(x);
        y = find(y);
        if (x != y) {
            if (rank[x] < rank[y]) {
                swap(x, y);
            }
            parent[y] = x;
            if (rank[x] == rank[y]) {
                rank[x]++;
            }
        }
    }

    bool is_connected(int x, int y) {
        return find(x) == find(y);
    }
};

struct Edge {
    int from, to, weight, id;

    Edge(int from, int to, int weight, int id) : from(from), to(to), weight(weight), id(id) {}
};

pair<int, vector<int>> Kruskal(vector<Edge>& edges, int ban, int n) {
    DSU dsu(n);
    vector<int> taken_edges;
    int MST_weight = 0, count_nodes = 0;
    for (auto const& e: edges) {
        if (!dsu.is_connected(e.from, e.to) && e.id != ban) {
            MST_weight += e.weight;
            taken_edges.push_back(e.id);
            count_nodes++;
            if (count_nodes == n - 1) {
                break;
            }
            dsu.connect(e.from, e.to);
        }
    }
    return {count_nodes == n - 1 ? MST_weight : INT32_MAX, taken_edges};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<Edge> edges;
    for (int i = 0; i < m; i++) {
        int from, to, weight;
        cin >> from >> to >> weight;
        edges.emplace_back(from - 1, to - 1, weight, i);
    }

    sort(edges.begin(), edges.end(), [](Edge const& a, Edge const& b) {
        return a.weight < b.weight;
    });

    auto [min1, taken_edges] = Kruskal(edges, -1, n);

    int min2 = INT32_MAX;
    for (int id: taken_edges) {
        min2 = min(min2, Kruskal(edges, id, n).first);
    }

    cout << min1 << " " << min2 << '\n';
}
