#include <iostream>
#include <vector>
#include <cmath>
#include <cfloat>

using namespace std;

typedef pair<int, int> point;

double get_distance(point const& a, point const& b) {
    return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}

double Prim(vector<point> const& graph) {
    int n = (int) graph.size();

    vector<bool> mark(n);
    vector<double> min_edge(n, DBL_MAX);
    min_edge[0] = DBL_MIN;

    double MST_weight = 0;
    while (true) {
        int v = -1;
        for (int i = 0; i < n; i++) {
            if (!mark[i] && (v == -1 || min_edge[i] < min_edge[v])) {
                v = i;
            }
        }
        if (v == -1) {
            break;
        }
        mark[v] = true;
        MST_weight += min_edge[v];
        for (int i = 0; i < n; i++) {
            if (!mark[i]) {
                double d = get_distance(graph[v], graph[i]);
                if (min_edge[i] > d) {
                    min_edge[i] = d;
                }
            }
        }
    }

    return MST_weight;
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

    printf("%.10f\n", Prim(graph));
}
