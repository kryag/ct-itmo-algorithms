//
// Created by Aleksandr Kiriak on 08.04.2024.
//
#include <bits/stdc++.h>

using namespace std;

struct Node {
    vector<int> edges;
};

struct Bipartite_Graph {
    void add_node(bool is_L_part) {
        if (is_L_part) {
            L.emplace_back();
        } else {
            R.emplace_back();
        }
    }

    void add_edge(int L_index, int R_index) {
        if (L_index >= L.size()) {
            L.resize(L_index + 1);
        }
        if (R_index >= R.size()) {
            R.resize(R_index + 1);
        }
        L[L_index].edges.push_back(R_index);
        R[R_index].edges.push_back(L_index);
    }

    int find_maximal_matching() {
        vector<int> p(R.size(), -1);
        mark.resize(L.size());
        int match_size = 0;
        for (int i = 0; i < L.size(); i++) {
            fill(mark.begin(), mark.end(), false);
            if (dfs(i, p)) {
                match_size++;
            }
        }
        return match_size;
    }

    int get_L_size() {
        return (int) L.size();
    }

    int get_R_size() {
        return (int) R.size();
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

struct Cell {
    int i, j;
    bool free;
    int index = -1;

    Cell(int i, int j, bool free) {
        this->i = i;
        this->j = j;
        this->free = free;
    }

    bool is_L_part() const {
        return i % 2 != 0 == j % 2;
    };
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m, a, b;
    cin >> n >> m >> a >> b;

    vector<vector<Cell>> board;
    for (int i = 0; i < n; i++) {
        board.emplace_back();
        for (int j = 0; j < m; j++) {
            char cell;
            cin >> cell;
            board[i].emplace_back(i, j, cell == '*');
        }
    }

    int free_cells = 0;
    Bipartite_Graph graph;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!board[i][j].free) {
                continue;
            }

            free_cells++;
            bool up = i > 0 && board[i - 1][j].free;
            bool left = j > 0 && board[i][j - 1].free;

            if (board[i][j].is_L_part()) {
                board[i][j].index = graph.get_L_size();
                graph.add_node(true);
                if (up) {
                    graph.add_edge(board[i][j].index, board[i - 1][j].index);
                }
                if (left) {
                    graph.add_edge(board[i][j].index, board[i][j - 1].index);
                }
            } else {
                board[i][j].index = graph.get_R_size();
                graph.add_node(false);
                if (up) {
                    graph.add_edge(board[i - 1][j].index, board[i][j].index);
                }
                if (left) {
                    graph.add_edge(board[i][j - 1].index, board[i][j].index);
                }
            }
        }
    }

    if (a > 2 * b) {
        cout << free_cells * b << endl;
        return 0;
    }

    int domino = graph.find_maximal_matching();
    cout << domino * a + (free_cells - 2 * domino) * b << endl;
}
