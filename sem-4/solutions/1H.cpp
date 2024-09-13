//
// Created by Aleksandr Kiriak on 09.04.2024.
//
#include <bits/stdc++.h>

using namespace std;

struct Edge {
    int index, v, u;

    Edge(int index, int v, int u) {
        this->index = index;
        this->v = v;
        this->u = u;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n, m;
        cin >> n >> m;

        vector<Edge> edges;
        for (int i = 0; i < m; i++) {
            int v, u;
            cin >> v >> u;
            edges.emplace_back(i, v - 1, u - 1);
        }

        unordered_set<int> matching_nodes;
        vector<int> matching_edges_id;
        for (const auto& edge : edges) {
            if (!matching_nodes.count(edge.v) && !matching_nodes.count(edge.u)) {
                matching_nodes.insert(edge.v);
                matching_nodes.insert(edge.u);
                matching_edges_id.push_back(edge.index);
                if (matching_edges_id.size() == n) {
                    break;
                }
            }
        }

        if (matching_edges_id.size() == n) {
            cout << "Matching" << endl;
            for (int edge_id : matching_edges_id) {
                cout << edge_id + 1 << " ";
            }
        } else {
            cout << "IndSet" << endl;
            int size = 0;
            for (int i = 0; i < 3 * n; i++) {
                if (!matching_nodes.count(i)) {
                    cout << i + 1 << " ";
                    size++;
                    if (size == n) {
                        break;
                    }
                }
            }
        }
        cout << endl;
    }
}
