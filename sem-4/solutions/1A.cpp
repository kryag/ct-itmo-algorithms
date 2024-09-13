//
// Created by Aleksandr Kiriak on 08.04.2024.
//
#include <bits/stdc++.h>

using namespace std;

struct Node {
    vector<int> edges;
};

struct Bipartite_Graph {
    Bipartite_Graph(int L_size, int R_size) {
        L.resize(L_size);
        R.resize(R_size);
    }

    void add_edge(int L_index, int R_index) {
        L[L_index].edges.push_back(R_index);
        R[R_index].edges.push_back(L_index);
    }

    pair<int, vector<int>> find_maximal_matching() {
        int match_size = 0;
        vector<int> p(R.size(), -1);
        mark.resize(L.size());
        for (int i = 0; i < L.size(); i++) {
            fill(mark.begin(), mark.end(), false);
            if (dfs(i, p)) {
                match_size++;
            }
        }
        return {match_size, p};
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

    Bipartite_Graph graph(n, m);

    for (int i = 0; i < n; i++) {
        while (true) {
            int edge;
            cin >> edge;
            if (edge == 0) {
                break;
            }
            edge--;
            graph.add_edge(i, edge);
        }
    }

    auto result = graph.find_maximal_matching();
    cout << result.first << endl;
    for (int i = 0; i < m; i++) {
        if (result.second[i] != -1) {
            cout << result.second[i] + 1 << " " << i + 1 << endl;
        }
    }
}
