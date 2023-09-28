#include <iostream>
#include <random>
#include <unordered_set>

std::unordered_set<int> tree_priority;
std::random_device random;
std::mt19937 generation(random());

int random_priority() {
    std::uniform_int_distribution<> distribution(INT32_MIN, INT32_MAX);
    return distribution(generation);
}

int get_priority() {
    int priority;
    while (true) {
        priority = random_priority();
        if (tree_priority.count(priority) == 0) {
            tree_priority.insert(priority);
            return priority;
        }
    }
}

struct Node {
    int x, y, min, sz;
    bool rev;
    Node *left, *right;

    explicit Node(int value) {
        x = value;
        y = get_priority();
        min = value;
        sz = 1;
        rev = false;
        left = nullptr;
        right = nullptr;
    }
};

int get_size(Node *v) {
    return v ? v->sz : 0;
}

int get_min(Node *v) {
    return v ? v->min : INT32_MAX;
}

void recalculate_parameters(Node *v) {
    if (v) {
        v->sz = 1 + get_size(v->left) + get_size(v->right);
        v->min = std::min(v->x, std::min(get_min(v->left), get_min(v->right)));
    }
}

void propagate(Node *v) {
    if (v && v->rev) {
        v->rev = false;
        std::swap(v->left, v->right);
        if (v->left) {
            v->left->rev ^= true;
        }
        if (v->right) {
            v->right->rev ^= true;
        }
    }
}

void split(Node *v, Node *&L, Node *&R, int x, int add) {
    if (!v) {
        return void(L = R = nullptr);
    }
    propagate(v);
    int cur_x = add + get_size(v->left);
    if (x <= cur_x) {
        split(v->left, L, v->left, x, add);
        R = v;
    } else {
        split(v->right, v->right, R, x, add + 1 + get_size(v->left));
        L = v;
    }
    recalculate_parameters(v);
}

void merge(Node*& v, Node *left, Node *right) {
    propagate(left);
    propagate(right);
    if (!left || !right) {
        v = left ? left : right;
    } else if (left->y > right->y) {
        merge(left->right, left->right, right);
        v = left;
    } else {
        merge(right->left, left, right->left);
        v = right;
    }
    recalculate_parameters(v);
}

Node *create_Cartesian_Tree(std::vector<int> &v) {
    Node *result = nullptr;
    for (int x: v) {
        merge(result, result, new Node(x));
    }
    return result;
}

int action(Node *v, int left, int right, bool is_min) {
    int answer = 0;
    Node *v1, *v2, *v3;
    split(v, v1, v2, left, 0);
    split(v2, v2, v3, right - left + 1, 0);
    if (is_min) {
        answer = v2->min;
    } else {
        v2->rev ^= true;
    }
    merge(v, v1, v2);
    merge(v, v, v3);
    return answer;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n, m, value, operation, left, right;
    std::vector<int> v;
    std::cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        std::cin >> value;
        v.push_back(value);
    }
    Node *root = create_Cartesian_Tree(v);
    for (; m > 0; --m) {
        std::cin >> operation >> left >> right;
        --left, --right;
        if (operation == 1) {
            action(root, left, right, false);
        } else {
            std::cout << action(root, left, right, true) << '\n';
        }
    }
    return 0;
}
