#include <vector>
#include <iostream>

struct Vertex {
    int no, number, depth, parent;
    std::vector<int> neighbours;

    Vertex(int no, int number) {
        this->no = no;
        this->number = number;
        depth = 0;
        parent = -1;
    }

    void set_parent(int p) {
        this->parent = p;
    }

    void add_neighbour(int n) {
        this->neighbours.push_back(n);
    }
};

std::vector<Vertex> tree;
std::vector<std::vector<int>> up;
std::vector<std::vector<long long>> sum;
std::vector<int> logs;

void dfs(int v, int depth) {
    tree[v].depth = depth;
    for (int n: tree[v].neighbours) {
        if (tree[n].no != tree[v].parent) {
            tree[n].set_parent(v);
            dfs(n, depth + 1);
        }
    }
}

void calculate_logs(unsigned long long n) {
    logs.push_back(0);
    logs.push_back(0);
    for (int i = 2; i < n + 1; i++) {
        logs.push_back(logs[i / 2] + 1);
    }
}

void binary_lifts() {
    up.emplace_back();
    sum.emplace_back();
    for (int v = 0; v < tree.size(); ++v) {
        up[0].push_back(tree[v].parent);
        sum[0].push_back(tree[v].number + tree[up[0][v]].number);
    }
    for (int k = 1; k < logs[tree.size()] + 1; ++k) {
        up.emplace_back();
        sum.emplace_back();
        for (int v = 0; v < tree.size(); ++v) {
            up[k].push_back(up[k - 1][up[k - 1][v]]);
            sum[k].push_back(sum[k - 1][v] + sum[k - 1][up[k - 1][v]] - tree[up[k - 1][v]].number);
        }
    }
}

long long getSum(int u, int v) {
    if (u == v) {
        return tree[u].number;
    }
    if (tree[u].depth < tree[v].depth) {
        std::swap(u, v);
    }
    long long answer = 0;
    for (int k = logs[tree.size()]; k >= 0; k--) {
        int nextU = up[k][u];
        long long sU = sum[k][u] - tree[up[k][u]].number;
        if (tree[nextU].depth >= tree[v].depth) {
            u = nextU;
            answer += sU;
        }
    }
    if (u == v) {
        return answer + tree[u].number;
    }
    for (int k = logs[tree.size()]; k >= 0; k--) {
        int nextU = up[k][u];
        int nextV = up[k][v];
        long long sU = sum[k][u] - tree[up[k][u]].number;
        long long sV = sum[k][v] - tree[up[k][v]].number;
        if (nextU != nextV) {
            u = nextU;
            v = nextV;
            answer += sU + sV;
        }
    }
    return answer + tree[u].number + tree[v].number + tree[tree[v].parent].number;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n, m, k, x, y;
    std::cin >> n;
    tree.emplace_back(0, 0);
    tree[0].set_parent(0);
    for (int i = 1; i <= n; ++i) {
        std::cin >> k;
        tree.emplace_back(i, k);
    }
    for (int i = 1; i < n; ++i) {
        std::cin >> x >> y;
        tree[x].add_neighbour(y);
        tree[y].add_neighbour(x);
    }
    tree[0].add_neighbour(1);
    dfs(0, -1);
    calculate_logs(tree.size());
    binary_lifts();
    std::cin >> m;
    for (int i = 0; i < m; ++i) {
        std::cin >> x >> y;
        std::cout << getSum(x, y) << '\n';
    }
    return 0;
}
