#include <iostream>
#include <vector>
#include <queue>

struct node {
    int deg{};
    std::vector<int> edges;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n, count, v;
    std::cin >> n;
    std::vector<node> graph(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> count;
        while (count--) {
            std::cin >> v;
            graph[i].edges.emplace_back(v - 1);
            ++graph[v - 1].deg;
        }
    }
    std::priority_queue<int> q;
    std::vector<int> top_sort;
    for (int i = 0; i < n; ++i) {
        if (!graph[i].deg) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        v = q.top();
        top_sort.emplace_back(v);
        q.pop();
        for (int i: graph[v].edges) {
            if (!--graph[i].deg) {
                q.push(i);
            }
        }
    }
    for (auto i = top_sort.rbegin(); i != top_sort.rend(); ++i) {
        std::cout << *i + 1 << " ";
    }
}
