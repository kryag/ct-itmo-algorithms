//
// Created by Aleksandr Kiriak on 14.05.2024.
//
#include <bits/stdc++.h>

using namespace std;

struct Edge {
    int id, from, to, capacity, flow;

    Edge(int id, int from, int to, int capacity, int flow) {
        this->id = id;
        this->from = from;
        this->to = to;
        this->capacity = capacity;
        this->flow = flow;
    }
};

struct Graph {
    static constexpr int INF = INT32_MAX;

    int size, s{}, t{};
    vector<Edge> edges;
    vector<vector<int>> g;
    vector<int> dist;
    vector<int> ptr;

    explicit Graph(int n) {
        this->size = n;
        g.resize(size, vector<int>());
        dist.resize(size);
        ptr.resize(size);
    }

    static int inv(int id) {
        return id ^ 1;
    }

    void add_edge(int a, int b, int c) {
        int e_size = (int) edges.size();
        edges.emplace_back(e_size, a, b, c, 0);
        g[a].push_back(e_size);
        edges.emplace_back(e_size + 1, b, a, 0, 0);
        g[b].push_back(e_size + 1);
    }

    int max_flow(int s_node, int t_node) {
        this->s = s_node;
        this->t = t_node;
        if (s == t) {
            return 0LL;
        }
        int result = 0;
        while (true) {
            bfs();
            if (dist[t] == INF) {
                break;
            }
            fill(ptr.begin(), ptr.end(), 0);
            int flow;
            do {
                flow = blocking_flow_dfs(s);
                result += flow;
            } while (flow > 0);
        }
        return result;
    }

    void bfs() {
        fill(dist.begin(), dist.end(), INF);
        dist[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : g[v]) {
                int to = edges[id].to;
                if (dist[to] == INF && edges[id].capacity > edges[id].flow) {
                    dist[to] = dist[v] + 1;
                    q.push(to);
                }
            }
        }
    }

    int blocking_flow_dfs(int v, int flow = INF) {
        if (v == t) {
            return flow == INF ? 0 : flow;
        }
        for (int i = ptr[v]; i < (int) g[v].size(); i++) {
            int id = g[v][i];
            if (dist[v] + 1 != dist[edges[id].to] || edges[id].capacity == edges[id].flow) {
                ptr[v]++;
                continue;
            }
            int rest_flow = blocking_flow_dfs(edges[id].to, min(flow, edges[id].capacity - edges[id].flow));
            if (rest_flow > 0) {
                edges[id].flow += rest_flow;
                edges[inv(id)].flow -= rest_flow;
                return rest_flow;
            } else {
                ptr[v]++;
            }
        }
        return 0;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> a(m);
    for (int& x : a) {
        cin >> x;
    }

    vector<vector<int>> teas(n);
    for (int i = 0; i < n; i++) {
        int count;
        cin >> count;
        while (count--) {
            int tea;
            cin >> tea;
            teas[i].push_back(tea - 1);
        }
    }

    int size = n + m + 2;
    int s = 0;
    int t = size - 1;

    int left = 0;
    int right = accumulate(a.begin(), a.end(), 0) + 1;
    while (left + 1 != right) {
        int mid = (left + right) / 2;

        Graph graph(size);
        for (int i = 0; i < n; i++) {
            graph.add_edge(s, i + 1, mid);
            for (int tea : teas[i]) {
                graph.add_edge(i + 1, n + 1 + tea, mid);
            }
        }
        for (int i = 0; i < m; i++) {
            graph.add_edge(n + 1 + i, t, a[i]);
        }

        int flow = graph.max_flow(s, t);
        if (flow == n * mid) {
            left = mid;
        } else {
            right = mid;
        }
    }

    cout << left << endl;
}
