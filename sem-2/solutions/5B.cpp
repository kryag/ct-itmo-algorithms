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
    int x, y, sz;
    Node *left, *right;

    explicit Node(int value) {
        x = value;
        y = get_priority();
        sz = 1;
        left = right = nullptr;
    }
};

int get_size(Node *v) {
    return v == nullptr ? 0 : v->sz;
}

void recalculate_size(Node *v) {
    if (v != nullptr) {
        v->sz = 1 + get_size(v->left) + get_size(v->right);
    }
}

void split(Node *v, int x, Node *&L, Node *&R) {
    if (v == nullptr) {
        L = R = nullptr;
        return;
    }
    if (get_size(v->left) < x) {
        split(v->right, x - get_size(v->left) - 1, v->right, R);
        L = v;
    } else {
        split(v->left, x, L, v->left);
        R = v;
    }
    recalculate_size(v);
}

Node *merge(Node *left, Node *right) {
    if (left == nullptr) {
        return right;
    }
    if (right == nullptr) {
        return left;
    }
    if (left->y > right->y) {
        left->right = merge(left->right, right);
        recalculate_size(left);
        return left;
    }
    right->left = merge(left, right->left);
    recalculate_size(right);
    return right;
}

Node *create_Cartesian_Tree(int n) {
    Node *result = nullptr;
    for (int i = 1; i <= n; ++i) {
        result = merge(result, new Node(i));
    }
    return result;
}

Node *VPERDE(Node *v, int left, int right) {
    Node *L1, *R1, *L2, *R2;
    split(v, right, L1, R1);
    split(L1, left - 1, L2, R2);
    return merge(merge(R2, L2), R1);
}

void inorder_traversal(Node *v) {
    if (v != nullptr) {
        inorder_traversal(v->left);
        std::cout << v->x << " ";
        inorder_traversal(v->right);
    }
}

int main() {
    int n, m, left, right;
    std::cin >> n >> m;
    Node *root = create_Cartesian_Tree(n);
    for (; m > 0; --m) {
        std::cin >> left >> right;
        VPERDE(root, left, right);
    }
    inorder_traversal(root);
    return 0;
}
