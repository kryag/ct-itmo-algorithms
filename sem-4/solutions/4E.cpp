//
// Created by Aleksandr Kiriak on 17.05.2024.
//
#include <bits/stdc++.h>

using namespace std;

const int INF = INT32_MAX;

int n, k, sz;
vector<vector<int>> g;
vector<vector<int>> capacity, cost;
vector<int> deg;

int min_cost_k_flow(int s, int t, int K) {
    vector<int> dist(sz), parent(sz), done(sz);
    int result = 0;

    while (K > 0) {
        for (int i = 0; i < sz; i++) {
            dist[i] = INF;
            parent[i] = -1;
            done[i] = false;
        }
        dist[s] = 0;
        while (true) {
            bool find = false;
            for (int i = 0; i < sz; i++) {
                if (dist[i] == INF || done[i]) {
                    continue;
                }
                done[i] = true;
                for (int j = 0; j < g[i].size(); j++) {
                    int to = g[i][j];
                    if (dist[to] > dist[i] + cost[i][to] && capacity[i][to] > 0) {
                        dist[to] = dist[i] + cost[i][to];
                        parent[to] = i;
                        done[to] = false;
                        find = true;
                    }
                }
            }
            if (!find) {
                break;
            }
        }
        if (dist[t] == INF) {
            break;
        }

        result += dist[t];
        K--;
        for (int cur = t; cur != s; cur = parent[cur]) {
            int v = parent[cur];
            capacity[v][cur]--;
            capacity[cur][v]++;
        }
    }

    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> k;
    vector<int> start(n), time(n), profit(n);

    vector<int> data;
    for (int i = 0; i < n; i++) {
        cin >> start[i] >> time[i];
        time[i] = time[i] + start[i];
        cin >> profit[i];
        data.push_back(start[i]);
        data.push_back(time[i]);
    }

    sort(data.begin(), data.end());
    data.erase(unique(data.begin(), data.end()), data.end());
    for (int i = 0; i < n; i++) {
        start[i] = (int) (lower_bound(data.begin(), data.end(), start[i]) - data.begin());
        time[i] = (int) (lower_bound(data.begin(), data.end(), time[i]) - data.begin());
    }

    int data_size = (int) data.size();
    sz = data_size + n;

    cost.resize(sz); capacity.resize(sz); deg.resize(sz); g.resize(sz);
    for (int i = 0; i < sz; i++) {
        cost[i].resize(sz);
        capacity[i].resize(sz);
    }

    auto add_edge = [&](int v, int u, int capacity_vu, int cost_vu, int capacity_uv, int cost_uv) {
        g[v].push_back(u);
        g[u].push_back(v);
        capacity[v][u] = capacity_vu;
        capacity[u][v] = capacity_uv;
        cost[v][u] = cost_vu;
        cost[u][v] = cost_uv;
    };

    for (int i = 0; i + 1 < data_size; i++) {
        add_edge(i, i + 1, INF, 0, 0, 0);
    }
    for (int i = 0; i < n; i++) {
        add_edge(start[i], data_size + i, 1, -profit[i], 0, profit[i]);
        add_edge(data_size + i, time[i], 1, 0, 0, 0);
    }

    min_cost_k_flow(0, data_size - 1, k);

    for (int i = 0; i < n; i++) {
        int v = start[i];
        cout << !capacity[v][data_size + i] << ' ';
    }
    cout << endl;
}
