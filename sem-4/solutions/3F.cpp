//
// Created by Aleksandr Kiriak on 13.05.2024.
//
#include <bits/stdc++.h>

using namespace std;

unordered_map<char, int> valence = {
        {'H', 1},
        {'O', 2},
        {'N', 3},
        {'C', 4}
};

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
        this->s = 0;
        this->t = size - 1;
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

    long long max_flow(int s_node, int t_node) {
        this->s = s_node;
        this->t = t_node;
        if (s == t) {
            return 0LL;
        }
        long long result = 0;
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

    vector<vector<char>> cells(n, vector<char>(m));
    vector<vector<int>> index(n, vector<int>(m));
    int size = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> cells[i][j];
            if (cells[i][j] == '.') {
                continue;
            }
            index[i][j] = size;
            size++;
        }
    }

    Graph graph(size + 1);
    int s = 0;
    int t = size;

    auto add_edge = [&](int from, int to_x, int to_y) {
        if (to_x < 0 || n <= to_x || to_y < 0 || m <= to_y || cells[to_x][to_y] == '.') {
            return;
        }
        graph.add_edge(from, index[to_x][to_y], 1);
    };

    int c_in = 0;
    int c_out = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (cells[i][j] == '.') {
                continue;
            }
            int cur_index = index[i][j];
            if (i % 2 == j % 2) {
                int val = valence[cells[i][j]];
                c_in += val;
                graph.add_edge(s, cur_index, val);
                add_edge(cur_index, i - 1, j);
                add_edge(cur_index, i + 1, j);
                add_edge(cur_index, i, j - 1);
                add_edge(cur_index, i, j + 1);
            } else {
                int val = valence[cells[i][j]];
                c_out += val;
                graph.add_edge(cur_index, t, val);
            }
        }
    }

    long long flow = graph.max_flow(s, t);
    cout << (graph.size > 2 && flow == c_in && flow == c_out ? "Valid" : "Invalid") << endl;
}
