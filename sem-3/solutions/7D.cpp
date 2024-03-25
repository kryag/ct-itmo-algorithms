#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

struct DSU {
    vector<int> p;

    explicit DSU(int size) {
        p.resize(size);
        for (int i = 0; i < size; i++) {
            p[i] = i;
        }
    }

    int find(int x) {
        if (p[x] != x) {
            p[x] = find(p[x]);
        }
        return p[x];
    }

    void join(int x, int y) {
        x = find(x);
        y = find(y);
        p[x] = y;
    }

    bool ask(int x, int y) {
        return find(x) == find(y);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    DSU dsu(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
    }

    vector<tuple<string, int, int>> action(k);
    for (int i = 0; i < k; i++) {
        cin >> get<0>(action[k - i - 1]) >> get<1>(action[k - i - 1]) >> get<2>(action[k - i - 1]);
    }

    vector<bool> answer(k - m);
    int index = k - m - 1;
    for (int i = 0; i < k; i++) {
        int u = get<1>(action[i]) - 1;
        int v = get<2>(action[i]) - 1;
        if (get<0>(action[i])[0] == 'a') {
            answer[index--] = dsu.ask(u, v);
        } else {
            dsu.join(u, v);
        }
    }

    for (auto const& b: answer) {
        cout << (b ? "YES" : "NO") << '\n';
    }
}
