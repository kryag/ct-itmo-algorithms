//
// Created by Aleksandr Kiriak on 24.06.2024.
//
#include <iostream>
#include <vector>

using namespace std;

struct Graph {
    static constexpr int UNINITIALIZED = -1;

    int n;
    vector<vector<int>> g;
    vector<int> match, parent, base, queue;
    vector<bool> mark, blossom;

    explicit Graph(int size) {
        n = size;
        g.resize(n);
        match.resize(n, UNINITIALIZED);
        parent.resize(n);
        base.resize(n);
        queue.resize(n);
        mark.resize(n);
        blossom.resize(n);
    }

    void add_edge(int from, int to, bool directed = false) {
        g[from].push_back(to);
        if (!directed) {
            g[to].push_back(from);
        }
    }

    pair<int, vector<int>> find_maximal_matching() {
        for (int i = 0; i < n; i++) {
            if (match[i] == UNINITIALIZED) {
                int v = dfs(i);
                while (v != UNINITIALIZED) {
                    int pv = parent[v];
                    int ppv = match[pv];
                    match[v] = pv;
                    match[pv] = v;
                    v = ppv;
                }
            }
        }

        int matching_number = 0;
        for (int i = 0; i < n; i++) {
            if (match[i] != UNINITIALIZED && i < match[i]) {
                matching_number++;
            }
        }

        return {matching_number, match};
    }

    int find_LCA(int v, int u) {
        vector<bool> cur_mark(n);
        while (true) {
            v = base[v];
            cur_mark[v] = true;
            if (match[v] == UNINITIALIZED) {
                break;
            }
            v = parent[match[v]];
        }
        while (true) {
            u = base[u];
            if (cur_mark[u]) {
                return u;
            }
            u = parent[match[u]];
        }
    }

    void mark_path(int v, int lca, int child) {
        while (base[v] != lca) {
            blossom[base[v]] = blossom[base[match[v]]] = true;
            parent[v] = child;
            child = match[v];
            v = parent[match[v]];
        }
    }

    int dfs(int from) {
        fill(mark.begin(), mark.end(), false);
        fill(parent.begin(), parent.end(), UNINITIALIZED);

        mark[from] = true;
        for (int i = 0; i < n; i++) {
            base[i] = i;
        }

        int head = 0;
        int tail = 0;
        queue[tail] = from;
        tail++;

        while (head < tail) {
            int v = queue[head];
            head++;
            for (int i = 0; i < (int) g[v].size(); i++) {
                int next = g[v][i];
                if (base[v] == base[next] || match[v] == next) {
                    continue;
                }
                if (next == from || match[next] != UNINITIALIZED && parent[match[next]] != UNINITIALIZED) {
                    int lca = find_LCA(v, next);
                    fill(blossom.begin(), blossom.end(), false);
                    mark_path(v, lca, next);
                    mark_path(next, lca, v);
                    for (int j = 0; j < n; j++) {
                        if (blossom[base[j]]) {
                            base[j] = lca;
                            if (!mark[j]) {
                                mark[j] = true;
                                queue[tail] = j;
                                tail++;
                            }
                        }
                    }
                } else if (parent[next] == UNINITIALIZED) {
                    parent[next] = v;
                    if (match[next] == UNINITIALIZED) {
                        return next;
                    }
                    next = match[next];
                    mark[next] = true;
                    queue[tail] = next;
                    tail++;
                }
            }
        }
        return UNINITIALIZED;
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
        int u, v;
        cin >> u >> v;
        graph.add_edge(u - 1, v - 1);
    }

    auto [matching_number, match] = graph.find_maximal_matching();

    cout << matching_number << endl;
    for (int i = 0; i < n; i++) {
        if (match[i] != Graph::UNINITIALIZED && i < match[i]) {
            cout << i + 1 << ' ' << match[i] + 1 << '\n';
        }
    }
}
