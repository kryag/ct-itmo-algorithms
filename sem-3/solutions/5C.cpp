#include <iostream>
#include <deque>
#include <vector>

using namespace std;

const int INFINITY = INT32_MAX;

struct Edge {
    int to, cost;

    Edge(int to, int cost) : to(to), cost(cost) {}
};

struct Node {
    vector<Edge> edges;
};

int bfs(vector<Node>& graph, int from, int to) {
    vector<int> cost(graph.size(), INFINITY);
    cost[from] = 0;

    deque<int> dq;
    dq.push_back(from);
    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();
        for (auto const& v: graph[u].edges) {
            if (cost[v.to] > cost[u] + v.cost) {
                cost[v.to] = cost[u] + v.cost;
                if (v.cost) {
                    dq.push_back(v.to);
                } else {
                    dq.push_front(v.to);
                }
            }
        }
    }

    return cost[to] == INFINITY ? -1 : cost[to];
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
        from--, to--;
        graph[from].edges.emplace_back(to, 0);
        graph[to].edges.emplace_back(from, 1);
    }

    int k;
    cin >> k;
    for (int i = 0; i < k; i++) {
        int s, t;
        cin >> s >> t;
        cout << bfs(graph, s - 1, t - 1) << '\n';
    }
}
