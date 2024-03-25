#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef pair<int, int> cell;

const int INFINITY = INT32_MAX;

struct Node {
    bool is_wall;
    vector<cell> edges;

    Node() : Node(false) {}

    explicit Node(bool is_wall) : is_wall(is_wall) {}
};

vector<vector<char>> bfs(vector<vector<Node>>& graph) {
    int n = (int) graph.size();
    int m = (int) graph.front().size();

    vector<vector<int>> dist(n, vector<int>(m, INFINITY));
    queue<cell> q;
    for (int i = 1; i < m - 1; i++) {
        dist[0][i] = 0;
        dist[n - 1][i] = 0;
        q.emplace(0, i);
        q.emplace(n - 1, i);
    }
    for (int i = 1; i < n - 1; i++) {
        dist[i][0] = 0;
        dist[i][m - 1] = 0;
        q.emplace(i, 0);
        q.emplace(i, m - 1);
    }

    vector<vector<char>> direction(n, vector<char>(m, '#'));
    while (!q.empty()) {
        auto [ux, uy] = q.front();
        q.pop();
        if (graph[ux][uy].is_wall) continue;
        for (auto const& [vx, vy]: graph[ux][uy].edges) {
            if (graph[vx][vy].is_wall) continue;
            if (dist[vx][vy] > dist[ux][uy] + 1) {
                dist[vx][vy] = dist[ux][uy] + 1;
                char c;
                if (vx == ux) {
                    if (uy + 1 == vy) {
                        c = '<';
                    } else {
                        c = '>';
                    }
                } else {
                    if (ux + 1 == vx) {
                        c = '^';
                    } else {
                        c = 'v';
                    }
                }
                direction[vx][vy] = c;
                q.emplace(vx, vy);
            }
        }
    }

    vector<vector<char>> ans(n - 2, vector<char>(m - 2));
    for (int i = 1; i < n - 1; i++) {
        for (int j = 1; j < m - 1; j++) {
            ans[i - 1][j - 1] = direction[i][j];
        }
    }
    return ans;
}

template <typename T>
void print_2d_vector(vector<vector<T>> const& v) {
    for (auto const& x: v) {
        for (auto const& xx: x) {
            cout << xx;
        }
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<Node>> graph(n + 2, vector<Node>(m + 2));

    auto add_edge = [&](int i1, int j1, int i2, int j2) {
        if (!graph[i1][j1].is_wall && !graph[i2][j2].is_wall) {
            graph[i1][j1].edges.emplace_back(i2, j2);
            graph[i2][j2].edges.emplace_back(i1, j1);
        }
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            cin >> c;
            if (c == '#') {
                graph[i + 1][j + 1].is_wall = true;
            } else {
                add_edge(i + 1, j + 1, i, j + 1);
                add_edge(i + 1, j + 1, i + 1, j);
            }
        }
        add_edge(i + 1, m + 1, i + 1, m);
    }
    for (int i = 1; i < m + 1; i++) {
        add_edge(n + 1, i, n, i);
    }

    print_2d_vector(bfs(graph));
}
