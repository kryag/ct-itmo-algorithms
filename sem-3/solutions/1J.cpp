#include <iostream>
#include <vector>

struct node {
    int time;
    std::vector<int> edges;

    explicit node(int time) {
        this->time = time;
    }
};

std::vector<node> graph;
std::vector<bool> mark;
std::vector<int> result;
long long T;

void dfs(int u) {
    mark[u] = true;
    for (int v: graph[u].edges) {
        if (!mark[v]) {
            dfs(v);
        }
    }
    T += graph[u].time;
    result.emplace_back(u);
}

int main() {
    int n, t, count;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> t;
        graph.emplace_back(t);
        mark.emplace_back();
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> count;
        while (count--) {
            std::cin >> t;
            graph[i].edges.emplace_back(t - 1);
        }
    }
    dfs(0);
    std::cout << T << " " << result.size() << '\n';
    for (int v: result) {
        std::cout << v + 1 << " ";
    }
}
