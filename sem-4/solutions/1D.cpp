//
// Created by Aleksandr Kiriak on 09.04.2024.
//
#include <bits/stdc++.h>

using namespace std;

struct Coordinate {
    int x, y;

    Coordinate() {
        x = 0;
        y = 0;
    }

    Coordinate(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

int travel_time(Coordinate from, Coordinate to) {
    return abs(from.x - to.x) + abs(from.y - to.y);
}

struct Node {
    int start_time;
    Coordinate start, finish;
    vector<int> edges;

    Node(int start_time, Coordinate start, Coordinate finish) {
        this->start_time = start_time;
        this->start = start;
        this->finish = finish;
    }

    bool have_time(const Node& another) const {
        return start_time + travel_time(start, finish) + travel_time(finish, another.start) < another.start_time;
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

    int M;
    cin >> M;

    vector<Node> nodes;
    for (int i = 0; i < M; i++) {
        char clock;
        int start_time = 0;

        cin >> clock;
        start_time += (clock - '0') * 10 * 60;

        cin >> clock;
        start_time += (clock - '0') * 60;

        cin >> clock;

        cin >> clock;
        start_time += (clock - '0') * 10;

        cin >> clock;
        start_time += clock - '0';

        int x_start;
        cin >> x_start;

        int y_start;
        cin >> y_start;

        int x_finish;
        cin >> x_finish;

        int y_finish;
        cin >> y_finish;

        nodes.emplace_back(start_time, Coordinate(x_start, y_start), Coordinate(x_finish, y_finish));
        for (int j = 0; j < i; j++) {
            if (nodes[j].have_time(nodes[i])) {
                nodes[j].edges.push_back(i);
            }
        }
    }

    Bipartite_Graph bipartite_graph(nodes);
    vector<int> matching = bipartite_graph.find_maximal_matching();

    Graph init_graph(nodes);
    for (int i = 0; i < M; i++) {
        if (matching[i] != -1) {
            init_graph.add_edge(matching[i], i);
        }
    }
    cout << init_graph.count_paths() << endl;
}
