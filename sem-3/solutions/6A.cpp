#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> point;

const int INFINITY = INT32_MAX;

int get_distance(point const& a, point const& b) {
    int x_diff = a.first - b.first;
    int y_diff = a.second - b.second;
    return x_diff * x_diff + y_diff * y_diff;
}

int Dijkstra(vector<point>& graph, int s, int t) {
    vector<bool> mark(graph.size());
    vector<int> dist(graph.size(), INFINITY);
    dist[s] = 0;

    while (true) {
        int v = -1;
        for (int i = 0; i < graph.size(); i++) {
            if (!mark[i] && (v == -1 || dist[i] < dist[v])) {
                v = i;
            }
        }
        if (v == -1) {
            break;
        }
        mark[v] = true;
        for (int i = 0; i < graph.size(); i++) {
            dist[i] = min(dist[i], dist[v] + get_distance(graph[v], graph[i]));
        }
    }

    return dist[t];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<point> graph(n);

    for (int i = 0; i < n; i++) {
        cin >> graph[i].first >> graph[i].second;
    }

    int s, t;
    cin >> s >> t;

    cout << Dijkstra(graph, s - 1, t - 1) << '\n';
}
