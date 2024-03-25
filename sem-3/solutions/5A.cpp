#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int INFINITY = INT32_MAX;

struct Node {
    vector<int> edges;
};

pair<int, vector<int>> bfs(vector<Node>& graph, int from, int to) {
    vector<int> dist(graph.size(), INFINITY);
    dist[from] = 0;
    vector<int> p(graph.size(), -1);
    queue<int> q;
    q.push(from);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v: graph[u].edges) {
            if (dist[v] == INFINITY) {
                dist[v] = dist[u] + 1;
                p[v] = u;
                q.push(v);
            }
        }
    }
    vector<int> path;
    int cur = to;
    while (p[cur] != -1 && cur != from) {
        path.push_back(cur);
        cur = p[cur];
    }
    path.push_back(from);
    return {dist[to], path};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<Node> graph(n);

    for (int i = 0; i < m; i++) {
        int from, to;
        cin >> from >> to;
        graph[from - 1].edges.push_back(to - 1);
    }

    int s, t;
    cin >> s >> t;
    auto ans = bfs(graph, s - 1, t - 1);
    if (ans.first == INFINITY) {
        cout << "-1" << '\n';
        return 0;
    }
    cout << ans.first << '\n';
    for (auto i = ans.second.rbegin(); i != ans.second.rend(); i++) {
        cout << *i + 1 << " ";
    }
}
