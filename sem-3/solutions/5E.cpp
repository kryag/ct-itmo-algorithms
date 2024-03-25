#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int INFINITY = INT32_MAX;

struct Edge {
    int to, type;

    Edge(int to, int type) : to(to), type(type) {}
};

struct Node {
    vector<Edge> edges;
};

vector<int> bfs(vector<Node>& graph, int start) {
    int n = (int) graph.size();

    vector<vector<int>> dist(2, std::vector<int>(n, INFINITY));
    dist[0][start] = 0;
    dist[1][start] = 0;

    queue<pair<int, int>> q;
    q.emplace(start, 0);
    q.emplace(start, 1);
    while (!q.empty()) {
        auto [from, prev_type] = q.front();
        q.pop();
        for (auto const& [to, type]: graph[from].edges) {
            if ((prev_type + type == 1) && dist[type][to] > dist[prev_type][from] + 1) {
                dist[type][to] = dist[prev_type][from] + 1;
                q.emplace(to, type);
            }
        }
    }

    vector<int> ans(n - 1);
    for (int i = 0; i != start && i < n; i++) {
        ans[i] = min(dist[0][i], dist[1][i]);
        if (ans[i] == INFINITY) {
            ans[i] = -1;
        }
    }

    return ans;
}

template <typename T>
void print_vector(vector<T> const& v) {
    for (auto const& x: v) {
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
        int from, to, type;
        cin >> from >> to >> type;
        graph[to - 1].edges.emplace_back(from - 1, type - 1);
    }

    print_vector(bfs(graph, n - 1));
}
