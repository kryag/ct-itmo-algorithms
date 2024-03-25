#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> edge;

const int INFINITY = INT32_MAX;
const int NO_PATH = 30'000;

struct Node {
    vector<edge> edges;
};

vector<int> Bellman_Ford(vector<Node>& graph, int s) {
    int n = (int) graph.size();
    vector<int> d(n, INFINITY);
    d[s] = 0;
    for (int k = 1; k < n; k++) {
        for (int v = 0; v < n; v++) {
            if (d[v] == INFINITY) continue;
            for (auto const& e: graph[v].edges) {
                d[e.first] = min(d[e.first], d[v] + e.second);
            }
        }
    }
    return d;
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
    }

    vector<int> d = Bellman_Ford(graph, 0);
    for (int x: d) {
        cout << (x == INFINITY ? NO_PATH : x) << " ";
    }
    cout << '\n';
}
