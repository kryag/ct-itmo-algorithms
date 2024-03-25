#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> edge;

const int INFINITY = INT32_MAX;

struct Node {
    vector<edge> edges;
};

vector<int> Bellman_Ford(vector<Node>& graph, int s, int k) {
    int n = (int) graph.size();

    vector<vector<int>> d(k + 1, vector<int>(n, INFINITY));
    d[0][s] = 0;

    for (int i = 1; i < k + 1; i++) {
        for (int v = 0; v < n; v++) {
            if (d[i - 1][v] == INFINITY) continue;
            for (auto const& [to, weight]: graph[v].edges) {
                if (d[i][to] > d[i - 1][v] + weight) {
                    d[i][to] = d[i - 1][v] + weight;
                }
            }
        }
    }

    vector<int> ans(n, INFINITY);
    for (int i = 0; i < n; i++) {
        ans[i] = d[k][i] == INFINITY ? -1 : d[k][i];
    }

    return ans;
}

template <typename T>
void print_vector(vector<T> const& v) {
    for (auto const& x: v) {
        cout << x << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, k, s;
    cin >> n >> m >> k >> s;
    vector<Node> graph(n);

    for (int i = 0; i < m; i++) {
        int from, to, weight;
        cin >> from >> to >> weight;
        graph[from - 1].edges.emplace_back(to - 1, weight);
    }

    print_vector(Bellman_Ford(graph, s - 1, k));
}
