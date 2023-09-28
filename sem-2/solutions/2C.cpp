#include <algorithm>
#include <vector>
#include <iostream>
#include <set>

struct Node {
    int left, right, size, min, count_min, add;
    bool flag_propagate;

    Node(int left, int right) {
        this->left = left;
        this->right = right;
        size = right - left;
        min = 0;
        count_min = size;
        add = 0;
        flag_propagate = false;
    }
};

struct Coordinate {
    int x, y1, y2, type;

    Coordinate(int x, int y1, int y2, int type) {
        this->x = x;
        this->y1 = y1;
        this->y2 = y2;
        this->type = type;
    }
};

std::vector<Node> tree;
std::vector<int> y;
int max_depth;

void propagate(int pos) {
    if (tree[pos].flag_propagate) {
        for (int i = 2 * pos + 1; i <= 2 * pos + 2; i++) {
            tree[i].add += tree[pos].add;
            tree[i].min += tree[pos].add;
            tree[i].flag_propagate = true;
        }
        tree[pos].add = 0;
        tree[pos].flag_propagate = false;
    }
}

void combine(int pos) {
    if (tree[2 * pos + 1].min < tree[2 * pos + 2].min) {
        tree[pos].min = tree[2 * pos + 1].min;
        tree[pos].count_min = tree[2 * pos + 1].count_min;
    } else if (tree[2 * pos + 2].min < tree[2 * pos + 1].min) {
        tree[pos].min = tree[2 * pos + 2].min;
        tree[pos].count_min = tree[2 * pos + 2].count_min;
    } else {
        tree[pos].min = tree[2 * pos + 2].min;
        tree[pos].count_min = tree[2 * pos + 1].count_min + tree[2 * pos + 2].count_min;
    }
}

std::pair<int, int> get() {
    return {tree[0].min, tree[0].count_min};
}

void add(int pos, int ql, int qr, int value) {
    if (tree[pos].right <= ql || qr <= tree[pos].left) {
        return;
    }
    if (ql <= tree[pos].left && tree[pos].right <= qr) {
        tree[pos].add += value;
        tree[pos].min += value;
        tree[pos].flag_propagate = true;
        return;
    }
    propagate(pos);
    add(2 * pos + 1, ql, qr, value);
    add(2 * pos + 2, ql, qr, value);
    combine(pos);
}

void build(int depth, int pos) {
    if (depth == max_depth) {
        int left = 0;
        int right = 0;
        bool flag = false;
        if (!y.empty()) {
            if (pos - tree.size() / 2 >= y.size()) {
                left = y.back();
                flag = true;
            } else {
                left = y[pos - tree.size() / 2];
            }
            if (pos - tree.size() / 2 + 1 >= y.size()) {
                right = y.back();
                flag = true;
            } else {
                right = y[pos - tree.size() / 2 + 1];
            }
        }
        tree[pos] = Node(left, right);
        if (flag) {
            tree[pos].min = 1'000'000'000;
        }
        return;
    }
    build(depth + 1, 2 * pos + 1);
    build(depth + 1, 2 * pos + 2);
    tree[pos] = Node(tree[2 * pos + 1].left, tree[2 * pos + 2].right);
    combine(pos);
}

int to2k(int x) {
    int a = 1;
    int pow = 0;
    while (true) {
        if (a >= x) {
            return pow;
        }
        a *= 2;
        pow++;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int N, x1, y1, x2, y2;
    std::cin >> N;
    std::vector<Coordinate> coordinates;
    std::set<int> y_coordinates;
    for (int i = 0; i < N; ++i) {
        std::cin >> x1 >> y1 >> x2 >> y2;
        coordinates.emplace_back(x1, y1, y2, 1);
        coordinates.emplace_back(x2, y1, y2, -1);
        y_coordinates.insert(y1);
        y_coordinates.insert(y2);
    }
    std::sort(coordinates.begin(), coordinates.end(), [](const Coordinate &f, const Coordinate &s) {
        if (f.x != s.x) {
            return f.x < s.x;
        } else {
            return f.type < s.type;
        }
    });
    for (int cur_y : y_coordinates) {
        y.push_back(cur_y);
    }
    if (y_coordinates.size() == 1) {
        for (int single_y: y_coordinates) {
            y.push_back(single_y);
        }
    }
    max_depth = to2k(y.size() - 1);
    for (int i = 0; i < 2 * (1 << max_depth) - 1; ++i) {
        tree.emplace_back(0, 0);
    }
    build(0, 0);
    long long answer = 0;
    int yMax = y.empty() ? 0 : y.back() - y[0];
    int xPrev = coordinates.empty() ? 0 : coordinates[0].x;
    for (Coordinate c: coordinates) {
        std::pair<int, int> cur = get();
        int countMin = (cur.first == 0) ? cur.second : 0;
        answer += (long long) (c.x - xPrev) * (yMax - countMin);
        add(0, c.y1, c.y2, c.type);
        xPrev = c.x;
    }
    std::cout << answer;
    return 0;
}
