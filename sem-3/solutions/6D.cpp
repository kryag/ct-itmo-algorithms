#include <iostream>
#include <vector>
#include <set>

using namespace std;

typedef pair<int, int> edge;

const int INFINITY = INT32_MAX;

struct Node {
    vector<edge> edges;
};

vector<int> Dijkstra(vector<Node>& graph, int s) {
    vector<int> d(graph.size(), INFINITY);
    d[s] = 0;

    set<pair<int, int>> set;
    set.emplace(0, 0);

    while (!set.empty()) {
        auto first = set.begin();
        int v = (*first).second;
        set.erase(first);
        for (auto const& e: graph[v].edges) {
            if (d[v] + e.second < d[e.first]) {
                set.erase({d[e.first], e.first});
                d[e.first] = d[v] + e.second;
                set.insert({d[e.first], e.first});
            }
        }
    }

    return d;
}

template <typename T>
void print_vector(vector<T> const& v) {
    for (T const& x: v) {
        cout << x << " ";
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<Node> graph(n);

    for (int i = 0; i < m; i++) {
        int from, to, weight;
        cin >> from >> to >> weight;
        graph[from - 1].edges.emplace_back(to - 1, weight);
        graph[to - 1].edges.emplace_back(from - 1, weight);
    }

    print_vector(Dijkstra(graph, 0));
}
