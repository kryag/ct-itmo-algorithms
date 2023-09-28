#include <iostream>
#include <vector>

struct vertex {
    int open;
    int close;
    int pair;

    void initialization() {
        open = 0;
        close = 0;
        pair = 0;
    }
};

int n;
std::vector<vertex> tree;

vertex merge(const vertex &left, const vertex &right){
    vertex parent{};
    parent.open = left.open + right.open;
    parent.close = left.close + right.close;
    int leftDist = std::max(left.open - left.pair / 2, 0);
    int rightDist = std::max(right.close - right.pair / 2, 0);
    parent.pair = left.pair + right.pair + 2 * (std::min(leftDist, rightDist));
    return parent;
}

void set(int v, int l, int r, int i, vertex value) {
    if (l + 1 == r) {
        tree[v] = value;
        return;
    }
    int m = l + (r - l) / 2;
    if (i < m) {
        set(2 * v + 1, l, m, i, value);
    } else {
        set(2 * v + 2, m, r, i, value);
    }
    tree[v] = merge(tree[2 * v + 1], tree[2 * v + 2]);
}

vertex getAnswer(int v, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) {
        vertex tmp{};
        tmp.initialization();
        return tmp;
    }
    if (ql <= l && r <= qr) {
        return tree[v];
    }
    int m = l + (r - l) / 2;
    vertex left = getAnswer(2 * v + 1, l, m, ql, qr);
    vertex right = getAnswer(2 * v + 2, m, r, ql, qr);
    return merge(left, right);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::string line;
    std::cin >> line;
    n = 1;
    while (n < line.length()) {
        n *= 2;
    }
    vertex zero{};
    zero.initialization();
    tree.assign(2 * n - 1, zero);
    for (int i = 0; i < line.length(); i++) {
        vertex temp{};
        temp.open = (line[i] == '(') ? 1 : 0;
        temp.close = (line[i] == ')') ? 1 : 0;
        temp.pair = 0;
        set(0, 0, n, i, temp);
    }
    int m;
    std::cin >> m;
    while (m > 0) {
        int ql, qr;
        std::cin >> ql >> qr;
        vertex answer = getAnswer(0, 0, n, ql - 1, qr);
        std::cout << answer.pair << '\n';
        m--;
    }
    return 0;
}
