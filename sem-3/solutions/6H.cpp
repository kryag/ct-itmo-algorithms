#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> edge;

const int INFINITY = INT32_MAX;
const int NO_EDGE = 100'000;

struct Node {
    vector<edge> edges;
};

vector<int> Bellman_Ford(vector<Node>& graph, int s) {
    int n = (int) graph.size();

    vector<int> d(n, INFINITY);
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        p[i] = i;
    }
    d[s] = 0;

    for (int i = 1; i < n; i++) {
        for (int v = 0; v < n; v++) {
            if (d[v] == INFINITY) continue;
            for (auto const& [to, weight]: graph[v].edges) {
                if (d[to] > d[v] + weight) {
                    d[to] = d[v] + weight;
                    p[to] = v;
                }
            }
        }
    }

    vector<int> cycle;
    for (int v = 0; v < n; v++) {
        if (d[v] == INFINITY) continue;
        for (auto [to, weight]: graph[v].edges) {
            if (d[to] > d[v] + weight) {
                for (int i = 0; i < n; i++) {
                    to = p[to];
                }
                int u = to;
                while (true) {
                    if (u == to && !cycle.empty()) {
                        break;
                    }
                    cycle.push_back(u);
                    u = p[u];
                }
                reverse(cycle.begin(), cycle.end());
                return cycle;
            }
        }
    }

    return cycle;
}

template <typename T>
void print_vector(vector<T> const& v) {
    for (auto const& x: v) {
        cout << x + 1 << " ";
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<Node> graph(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int weight;
            cin >> weight;
            if (weight != NO_EDGE) {
                graph[i].edges.emplace_back(j, weight);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        auto v = Bellman_Ford(graph, i);
        if (!v.empty()) {
            cout << "YES" << '\n';
            cout << v.size() << '\n';
            print_vector(v);
            return 0;
        }
    }
    cout << "NO" << '\n';
}
