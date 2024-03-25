#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int INFINITY = INT32_MAX;

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
    int from, to, weight;

    Edge(int from, int to, int weight) : from(from), to(to), weight(weight) {}
};

int Kruskal(vector<Edge>& edges, int n, int min_weight) {
    DSU dsu(n);
    int max_weight = 0, count_nodes = 0;
    for (auto const& e: edges) {
        if (!dsu.is_connected(e.from, e.to) && e.weight >= min_weight) {
            max_weight = e.weight;
            count_nodes++;
            if (count_nodes == n - 1) {
                break;
            }
            dsu.connect(e.from, e.to);
        }
    }
    return count_nodes == n - 1 ? (max_weight - min_weight) : INFINITY;
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
        edges.emplace_back(from - 1, to - 1, weight);
    }

    sort(edges.begin(), edges.end(), [](Edge const& a, Edge const& b) {
        return a.weight < b.weight;
    });

    int min_diff = INFINITY;
    for (int i = 0; i < m; i++) {
        min_diff = min(min_diff, Kruskal(edges, n, edges[i].weight));
    }

    if (min_diff == INFINITY) {
        cout << "NO" << '\n';
    } else {
        cout << "YES" << '\n';
        cout << min_diff << '\n';
    }
}
