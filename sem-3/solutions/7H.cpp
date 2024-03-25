#include <iostream>
#include <vector>
#include <set>

using namespace std;

vector<set<int>> edges;
set<int> not_mark;

void dfs(int u) {
    not_mark.erase(u);
    vector<int> v;
    for (int x: not_mark) {
        if (edges[u].find(x) == edges[u].end()) {
            v.push_back(x);
        }
    }
    for (int x: v) {
        not_mark.erase(x);
    }
    for (int x: v) {
        dfs(x);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;

    edges.resize(n);
    for (int i = 0; i < n; i++) {
        not_mark.insert(i);
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        edges[u - 1].insert(v - 1);
        edges[v - 1].insert(u - 1);
    }

    int count = 0;
    for (int u = 0; u < n; u++) {
        if (not_mark.find(u) != not_mark.end()) {
            dfs(u);
            count++;
        }
    }

    cout << count - 1 << '\n';
}
