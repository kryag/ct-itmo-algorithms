//
// Created by Aleksandr Kiriak on 08.04.2024.
//
#include <bits/stdc++.h>

using namespace std;

struct Node {
    vector<int> edges;
};

struct Graph {
    explicit Graph(int size) {
        nodes.resize(size);
        deg.resize(size);
    }

    void add_edge(int from, int to) {
        nodes[from].edges.push_back(to);
        deg[to]++;
    }

    int count_paths() {
        int leaves = 0;
        for (int i = 0; i < nodes.size(); i++) {
            if (deg[i] == 0) {
                leaves++;
            }
        }
        return leaves;
    }

private:
    vector<Node> nodes;
    vector<int> deg;
};

struct Bipartite_Graph {
    Bipartite_Graph(int L_size, int R_size) {
        L.resize(L_size);
        R.resize(R_size);
    }

    void add_edge(int L_index, int R_index) {
        L[L_index].edges.push_back(R_index);
    }

    vector<int> find_maximal_matching() {
        vector<int> p(R.size(), -1);
        mark.resize(L.size());
        for (int i = 0; i < L.size(); i++) {
            fill(mark.begin(), mark.end(), false);
            dfs(i, p);
        }
        return p;
    }

private:
    vector<Node> L, R;
    vector<bool> mark;

    bool dfs(int v, vector<int> &p) {
        if (mark[v]) return false;
        mark[v] = true;
        for (int to: L[v].edges) {
            if (p[to] == -1) {
                p[to] = v;
                return true;
            }
        }
        for (int to: L[v].edges) {
            if (dfs(p[to], p)) {
                p[to] = v;
                return true;
            }
        }
        return false;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    cin >> n >> m;

    Bipartite_Graph bipartite_graph(n, n);

    for (int i = 0; i < m; i++) {
        int v, u;
        cin >> v >> u;
        v--; u--;
        bipartite_graph.add_edge(v, u);
    }

    vector<int> matching = bipartite_graph.find_maximal_matching();
    Graph init_graph(n);
    for (int i = 0; i < n; i++) {
        if (matching[i] != -1) {
            init_graph.add_edge(matching[i], i);
        }
    }
    cout << init_graph.count_paths() << endl;
}
