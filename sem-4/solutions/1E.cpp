//
// Created by Aleksandr Kiriak on 09.04.2024.
//
#include <bits/stdc++.h>

using namespace std;

struct Node {
    unordered_set<int> ingredients;
    vector<int> edges;

    bool can_add_edge(const Node& other) {
        return all_of(ingredients.begin(), ingredients.end(), [&other](const auto& ingredient) {
            return other.ingredients.count(ingredient);
        });
    }
};

struct Graph {
    vector<Node> nodes;
    vector<int> deg;

    explicit Graph(const vector<Node>& nodes) {
        this->nodes = nodes;
        deg.resize(nodes.size());
        for (int i = 0; i < nodes.size(); i++) {
            this->nodes[i].edges.clear();
        }
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
};

struct Bipartite_Graph {
    vector<Node> L, R;
    vector<bool> mark;

    explicit Bipartite_Graph(const vector<Node>& nodes) {
        this->L = nodes;
        this->R = nodes;

        for (int i = 0; i < nodes.size(); i++) {
            R[i].edges.clear();
        }
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

    int N;
    cin >> N;

    vector<Node> nodes;
    unordered_map<string, int> ingredient_id;
    int id = 0;

    for (int i = 0; i < N; i++) {
        int k;
        cin >> k;

        Node node;
        for (int j = 0; j < k; j++) {
            string ingredient;
            cin >> ingredient;
            if (!ingredient_id.count(ingredient)) {
                ingredient_id[ingredient] = id;
                id++;
            }
            node.ingredients.insert(ingredient_id[ingredient]);
        }

        bool same = false;
        for (auto & other : nodes) {
            if (other.can_add_edge(node) && node.can_add_edge(other)) {
                same = true;
                break;
            }
        }
        if (!same) {
            nodes.push_back(node);
        }
    }

    int size = (int) nodes.size();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) {
                continue;
            }
            if (nodes[i].can_add_edge(nodes[j])) {
                nodes[i].edges.push_back(j);
            }
        }
    }

    Bipartite_Graph bipartite_graph(nodes);
    vector<int> matching = bipartite_graph.find_maximal_matching();

    Graph init_graph(nodes);
    for (int i = 0; i < size; i++) {
        if (matching[i] != -1) {
            init_graph.add_edge(matching[i], i);
        }
    }

    cout << init_graph.count_paths() << endl;
}
