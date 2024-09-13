//
// Created by Aleksandr Kiriak on 13.05.2024.
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
    vector<bool> mark;

    explicit Graph(int n) {
        this->size = n;
        g.resize(size, vector<int>());
        dist.resize(size);
        ptr.resize(size);
        mark.resize(size);
    }

    static int inv(int id) {
        return id ^ 1;
    }

    static int is_back_edge(int id) {
        return id % 2;
    }

    void add_edge(int a, int b, int c) {
        int e_size = (int) edges.size();
        edges.emplace_back(e_size, a, b, c, 0);
        g[a].push_back(e_size);
        edges.emplace_back(e_size + 1, b, a, 0, 0);
        g[b].push_back(e_size + 1);
    }

    long long max_flow(int s_node, int t_node) {
        this->s = s_node;
        this->t = t_node;
        if (s == t) {
            return 0;
        }
        while (true) {
            bfs();
            if (dist[t] == INF) {
                break;
            }
            fill(ptr.begin(), ptr.end(), 0);
            int flow;
            do {
                flow = blocking_flow_dfs(s);
            } while (flow > 0);
        }
        long long result = 0LL;
        for (int id : g[s]) {
            result += edges[id].flow;
        }
        return result;
    }

    vector<Edge> min_cut() {
        vector<Edge> answer;
        fill(mark.begin(), mark.end(), false);
        dfs(s);
        for (auto e : edges) {
            if (is_back_edge(e.id)) {
                continue;
            }
            if (mark[e.from] ^ mark[e.to]) {
                answer.push_back(e);
            }
        }
        return answer;
    }

    void dfs(int u) {
        mark[u] = true;
        for (int id : g[u]) {
            int v = edges[id].to;
            if (!mark[v] && edges[id].capacity > edges[id].flow) {
                dfs(v);
            }
        }
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
    Graph graph(n);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        graph.add_edge(a - 1, b - 1, c);
    }

    auto max_flow = graph.max_flow(0, n - 1);
    cout << max_flow << endl;
}
