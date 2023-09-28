#include <iostream>

const int MOD = 1'000'000'000;

struct Node {
    int value, min, max, height;
    long long sum;
    Node *left, *right;

    explicit Node(int x) {
        value = min = max = x;
        sum = x;
        height = 1;
        left = nullptr;
        right = nullptr;
    }
};

int get_height(Node *v) {
    return v == nullptr ? 0 : v->height;
}

int get_min(Node *v) {
    return v == nullptr ? INT32_MAX : v->min;
}

int get_max(Node *v) {
    return v == nullptr ? INT32_MIN : v->max;
}

long long get_sum(Node *v) {
    return v == nullptr ? 0 : v->sum;
}

int get_balance(Node *v) {
    return get_height(v->right) - get_height(v->left);
}

void recalculate_parameters(Node *v) {
    v->min = std::min(v->value, std::min(get_min(v->left), get_min(v->right)));
    v->max = std::max(v->value, std::max(get_max(v->left), get_max(v->right)));
    v->height = 1 + std::max(get_height(v->left), get_height(v->right));
    v->sum = v->value + get_sum(v->left) + get_sum(v->right);
}

Node *rotate_left(Node *v) {
    Node *right = v->right;
    v->right = right->left;
    right->left = v;
    recalculate_parameters(v);
    recalculate_parameters(right);
    return right;
}

Node *rotate_right(Node *v) {
    Node *left = v->left;
    v->left = left->right;
    left->right = v;
    recalculate_parameters(v);
    recalculate_parameters(left);
    return left;
}

Node *balance(Node *v) {
    int balance = get_balance(v);
    if (balance == 2) {
        if (get_balance(v->right) < 0) {
            v->right = rotate_right(v->right);
        }
        return rotate_left(v);
    }
    if (balance == -2) {
        if (get_balance(v->left) > 0) {
            v->left = rotate_left(v->left);
        }
        return rotate_right(v);
    }
    return v;
}

Node *find(Node *v, int value) {
    if (v == nullptr || v->value == value) {
        return v;
    }
    return find(v->value < value ? v->right : v->left, value);
}

bool contains(Node *v, int value) {
    return find(v, value) != nullptr;
}

Node *add_if_unique(Node *v, int value) {
    if (v == nullptr) {
        return new Node(value);
    }
    if (value < v->value) {
        v->left = add_if_unique(v->left, value);
    } else {
        v->right = add_if_unique(v->right, value);
    }
    recalculate_parameters(v);
    return balance(v);
}

Node *add(Node *v, int value) {
    return contains(v, value) ? v : add_if_unique(v, value);
}


long long get_sum_between(Node *v, int left, int right) {
    if (v == nullptr) {
        return 0LL;
    }
    if (v->min >= left && v->max <= right) {
        return v->sum;
    }
    if (v->value < left) {
        return get_sum_between(v->right, left, right);
    }
    if (v->value > right) {
        return get_sum_between(v->left, left, right);
    }
    return v->value + get_sum_between(v->left, left, right) + get_sum_between(v->right, left, right);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    Node *root = nullptr;
    int n, left, right, value;
    char command;
    bool prev_question = false;
    long long prev_answer = 0LL;
    std::cin >> n;
    for (; n > 0; --n) {
        std::cin >> command;
        if (command == '+') {
            std::cin >> value;
            root = add(root, prev_question ? ((int) ((value + prev_answer) % MOD)) : value);
            prev_question = false;
        } else {
            std::cin >> left >> right;
            prev_answer = get_sum_between(root, left, right);
            std::cout << prev_answer << '\n';
            prev_question = true;
        }
    }
    return 0;
}
