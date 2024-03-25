#include <algorithm>
#include <iostream>
#include <vector>

const int MAX_N = 100010, CONSTANT = 256;

struct node {
    int deg_in{}, deg_out{};
    std::vector<int> edges;
};

std::vector<node> graph(MAX_N);
std::vector<int> path;

void dfs(int u) {
    while (graph[u].deg_out) {
        dfs(graph[u].edges[graph[u].deg_out-- - 1]);
    }
    path.push_back(u);
}

void say_NO() {
    std::cout << "NO";
    exit(0);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, start;
    std::string s;
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        std::cin >> s;
        start = s[0] * CONSTANT + s[1];
        int end = s[1] * CONSTANT + s[2];
        graph[start].edges.emplace_back(end);
        ++graph[end].deg_in;
        ++graph[start].deg_out;
    }

    int count_start = 0, count_end = 0, count_bad = 0;
    for (int i = 0; i < MAX_N; ++i) {
        if (graph[i].deg_in == graph[i].deg_out) continue;
        if (graph[i].deg_out - graph[i].deg_in == 1) {
            start = i;
            ++count_start;
        } else if (graph[i].deg_in - graph[i].deg_out == 1) {
            ++count_end;
        } else {
            ++count_bad;
        }
    }
    if (count_bad > 0 || count_start != count_end || count_start > 1 || count_end > 1) {
        say_NO();
    }

    dfs(start);
    if (path.size() != n + 1) {
        say_NO();
    }

    reverse(path.begin(), path.end());
    std::string ans;
    ans += path[0] / CONSTANT;
    for (int p: path) {
        ans += p % CONSTANT;
    }

    std::cout << "YES" << '\n';
    std::cout << ans;
}
