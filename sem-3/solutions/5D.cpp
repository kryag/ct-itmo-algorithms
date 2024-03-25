#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int N = 10'000;
const int INFINITY = INT32_MAX;

struct Node {
    vector<int> edges;
};

vector<int> bfs(vector<Node>& graph, int from, int to) {
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
    while (p[to] != -1 && to != from) {
        path.push_back(to);
        to = p[to];
    }
    path.push_back(from);

    return path;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<Node> graph(N);
    for (int i = 1111; i < N; i++) {
        if (i % 1000 != 9) {
            graph[i].edges.push_back(i + 1000);
        }
        if (i % 10 != 1) {
            graph[i].edges.push_back(i - 1);
        }
        graph[i].edges.push_back((i % 1000) * 10 + (i / 1000));
        graph[i].edges.push_back((i % 10) * 1000 + (i / 10));
    }

    int from, to;
    cin >> from >> to;

    vector<int> ans = bfs(graph, from, to);
    for (auto i = ans.rbegin(); i != ans.rend(); i++) {
        cout << *i << '\n';
    }
}
