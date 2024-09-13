//
// Created by Aleksandr Kiriak on 15.05.2024.
//
#include <bits/stdc++.h>

using namespace std;

struct Edge {
    int id, from, to, capacity, flow, cost;

    Edge(int id, int from, int to, int capacity, int flow, int cost) {
        this->id = id;
        this->from = from;
        this->to = to;
        this->capacity = capacity;
        this->flow = flow;
        this->cost = cost;
    }
};

struct Graph {
    static constexpr int INF = INT32_MAX;

    int size, s{}, t{};
    vector<Edge> edges;
    vector<vector<int>> g;

    explicit Graph(int n) {
        this->size = n;
        g.resize(size, vector<int>());
    }

    static int inv(int id) {
        return id ^ 1;
    }

    void add_edge(int from, int to, int capacity, int cost) {
        int e_size = (int) edges.size();
        edges.emplace_back(e_size, from, to, capacity, 0, cost);
        g[from].push_back(e_size);
        edges.emplace_back(e_size + 1, to, from, 0, 0, -cost);
        g[to].push_back(e_size + 1);
    }

    long long min_cost_max_flow(int s_node, int t_node) {
        this->s = s_node;
        this->t = t_node;
        long long cost = 0LL;
        while (true) {
            vector<int> set_id(size), dist(size, INF), q(size), parent(size), parent_edge(size);
            int q_head = 0, q_tail = 0;
            q[q_tail++] = s;
            dist[s] = 0;
            while (q_head != q_tail) {
                int v = q[q_head++];
                set_id[v] = 2;
                if (q_head == size) {
                    q_head = 0;
                }
                for (int i = 0; i < (int) g[v].size(); i++) {
                    Edge& e = edges[g[v][i]];
                    if (e.flow < e.capacity && dist[v] + e.cost < dist[e.to]) {
                        dist[e.to] = dist[v] + e.cost;
                        if (set_id[e.to] == 0) {
                            q[q_tail++] = e.to;
                            if (q_tail == size) {
                                q_tail = 0;
                            }
                        } else if (set_id[e.to] == 2) {
                            if (--q_head == -1) {
                                q_head = size - 1;
                            }
                            q[q_head] = e.to;
                        }
                        parent[e.to] = v;
                        parent_edge[e.to] = i;
                        set_id[e.to] = 1;
                    }
                }
            }
            if (dist[t] == INF) {
                break;
            }
            int add_flow = INF;
            for (int v = t; v != s; v = parent[v]) {
                int parent_v = parent[v], parent_edge_v = parent_edge[v];
                add_flow = min(add_flow, edges[g[parent_v][parent_edge_v]].capacity - edges[g[parent_v][parent_edge_v]].flow);
            }
            for (int v = t; v != s; v = parent[v]) {
                int parent_v = parent[v], parent_edge_v = parent_edge[v], u = inv(g[parent_v][parent_edge_v]);
                cost += (long long) edges[g[parent_v][parent_edge_v]].cost * add_flow;
                edges[g[parent_v][parent_edge_v]].flow += add_flow;
                edges[u].flow -= add_flow;
            }
        }
        return cost;
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
        int from, to, capacity, cost;
        cin >> from >> to >> capacity >> cost;
        graph.add_edge(from - 1, to - 1, capacity, cost);
    }

    int s = 0;
    int t = n - 1;
    cout << graph.min_cost_max_flow(s, t) << endl;
}
