//
// Created by Aleksandr Kiriak on 09.04.2024.
//
#include <bits/stdc++.h>

using namespace std;

struct Node {
    vector<int> edges;
};

struct Graph {
    vector<Node> nodes;
    vector<bool> mark;

    explicit Graph(int size) {
        nodes.resize(size);
        mark.resize(size);
        fill(mark.begin(), mark.end(), false);
    }

    void add_edge(int from, int to) {
        nodes[from].edges.push_back(to);
    }

    void dfs(int v) {
        if (mark[v]) return;
        mark[v] = true;
        for (int to : nodes[v].edges) {
            if (!mark[to]) {
                dfs(to);
            }
        }
    }
};

template <typename T>
void print_vector(vector<T> v) {
    for (auto const& elem : v) {
        cout << to_string(elem) << " ";
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int m, n;
    cin >> m >> n;

    vector<vector<int>> edges(m);
    for (int L = 0; L < m; L++) {
        int K;
        cin >> K;
        for (int R = 0; R < K; R++) {
            int node;
            cin >> node;
            edges[L].push_back(node - 1);
        }
    }

    vector<int> match_node(m);
    int match_size = 0;
    for (int L = 0; L < m; L++) {
        cin >> match_node[L];
        match_node[L]--;
        if (match_node[L] != -1) {
            match_size++;
        }
    }

    Graph graph(m + n);
    for (int L = 0; L < m; L++) {
        for (int R : edges[L]) {
            if (match_node[L] == R) {
                graph.add_edge(R + m, L);
            } else {
                graph.add_edge(L, R + m);
            }
        }
    }

    for (int L = 0; L < m; L++) {
        if (match_node[L] == -1) {
            graph.dfs(L);
        }
    }

    vector<int> L_result;
    for (int L = 0; L < m; L++) {
        if (!graph.mark[L]) {
            L_result.push_back(L + 1);
        }
    }

    vector<int> R_result;
    for (int R = m; R < n + m; R++) {
        if (graph.mark[R]) {
            R_result.push_back(R + 1 - m);
        }
    }

    cout << match_size << endl;
    cout << L_result.size() << " ";
    print_vector(L_result);
    cout << R_result.size() << " ";
    print_vector(R_result);
}
