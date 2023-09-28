#include <bits/stdc++.h>
#include <vector>
#include <map>
#include <iostream>

struct Node {
    int depth, parent;
    bool can_go_to_parent;
    std::map<int, bool> neighbours;

    Node() {
        depth = 0;
        parent = -1;
        can_go_to_parent = false;
    }
};

Node *tree;
bool *visited;
int *up;
int *normal_up;
int *reverse_up;
int *logs;
int N;

void iterative_dfs(std::pair<int, int> v) {
    std::stack<std::pair<int, int>> st;
    st.push(v);
    while (!st.empty()) {
        v = st.top();
        st.pop();
        if (visited[v.first]) {
            continue;
        }
        visited[v.first] = true;
        tree[v.first].depth = v.second;
        for (auto &n: tree[v.first].neighbours) {
            if (!visited[n.first]) {
                tree[n.first].parent = v.first;
                tree[n.first].can_go_to_parent = tree[n.first].neighbours.find(v.first)->second;
                st.emplace(n.first, v.second + 1);
            }
        }
    }
}

void calculate_logs(int n) {
    logs = new int[n + 1];
    logs[0] = 0;
    logs[1] = 0;
    for (int i = 2; i < n + 1; ++i) {
        logs[i] = logs[i / 2] + 1;
    }
}

void calculate_binary_lifts() {
    up = new int[(logs[N] + 1) * N];
    normal_up = new int[(logs[N] + 1) * N];
    reverse_up = new int[(logs[N] + 1) * N];
    for (int v = 0; v < N; ++v) {
        up[v] = tree[v].parent;
        normal_up[v] = tree[v].can_go_to_parent ? tree[v].parent : v;
        reverse_up[v] = tree[v].can_go_to_parent ? v : tree[v].parent;
    }
    for (int k = 1; k < logs[N] + 1; ++k) {
        for (int v = 0; v < N; ++v) {
            up[k * N + v] = up[(k - 1) * N + up[(k - 1) * N + v]];
            normal_up[k * N + v] = normal_up[(k - 1) * N + normal_up[(k - 1) * N + v]];
            reverse_up[k * N + v] = reverse_up[(k - 1) * N + reverse_up[(k - 1) * N + v]];
        }
    }
}

bool can_escape(int b, int esc) {
    if (b == esc) {
        return true;
    }
    if (tree[b].depth > tree[esc].depth) {
        for (int k = logs[N]; k >= 0; --k) {
            int nextB = normal_up[k * N + b];
            if (tree[nextB].depth >= tree[esc].depth) {
                b = nextB;
            }
        }
        if (tree[b].depth != tree[esc].depth) {
            return false;
        }
        if (b == esc) {
            return true;
        }
    } else if (tree[b].depth < tree[esc].depth) {
        for (int k = logs[N]; k >= 0; --k) {
            int nextEsc = reverse_up[k * N + esc];
            if (tree[nextEsc].depth >= tree[b].depth) {
                esc = nextEsc;
            }
        }
        if (tree[b].depth != tree[esc].depth) {
            return false;
        }
        if (b == esc) {
            return true;
        }
    }
    int lcaB = b;
    int lcaEsc = esc;
    for (int k = logs[N]; k >= 0; --k) {
        int nextLcaB = up[k * N + lcaB];
        int nextLcaEsc = up[k * N + lcaEsc];
        if (nextLcaB != nextLcaEsc) {
            lcaB = nextLcaB;
            lcaEsc = nextLcaEsc;
            b = normal_up[k * N + b];
            esc = reverse_up[k * N + esc];
            if (b != lcaB || esc != lcaEsc) {
                return false;
            }
        }
    }
    return normal_up[b] == reverse_up[esc];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int m, a, b, esc;
    std::cin >> N;
    tree = new Node[N];
    for (int i = 0; i < N; ++i) {
        tree[i] = Node();
    }
    for (int i = 0; i < N - 1; ++i) {
        std::cin >> a >> b;
        --a;
        --b;
        tree[a].neighbours.insert(std::make_pair(b, true));
        tree[b].neighbours.insert(std::make_pair(a, false));
    }
    tree[0].parent = 0;
    visited = new bool[N];
    for (int i = 0; i < N; ++i) {
        visited[i] = false;
    }
    iterative_dfs(std::make_pair(0, 0));
    calculate_logs(N);
    calculate_binary_lifts();
    std::cin >> m;
    for (; m > 0; --m) {
        std::cin >> b >> esc;
        --b, --esc;
        std::cout << (can_escape(b, esc) ? "Yes" : "No") << '\n';
    }
    delete[] tree;
    delete[] up;
    delete[] normal_up;
    delete[] reverse_up;
    delete[] logs;
    return 0;
}
