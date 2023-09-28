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
    int value, y, sz;
    long long sum;
    Node *left, *right;

    explicit Node(int value) {
        this->value = value;
        y = get_priority();
        sz = 1;
        sum = value;
        left = nullptr;
        right = nullptr;
    }
};

int get_size(Node *v) {
    return v ? v->sz : 0;
}

long long get_sum(Node *v) {
    return v ? v->sum : 0;
}

void recalculate_parameters(Node *v) {
    if (v) {
        v->sz = 1 + get_size(v->left) + get_size(v->right);
        v->sum = v->value + get_sum(v->left) + get_sum(v->right);
    }
}

void split(Node *v, Node *&L, Node *&R, int x, int add) {
    if (!v) {
        return void(L = R = nullptr);
    }
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

void swapper(Node *&even, Node *&odd, int left, int right) {
    int left_even = (left + 1) / 2;
    int right_even = right / 2;
    int left_odd = left / 2;
    int right_odd = (right - 1) / 2;
    Node *v1, *v2, *v3, *v4, *v5, *v6;
    split(even, v1, v2, left_even, 0);
    split(v2, v2, v3, right_even - left_even + 1, 0);
    split(odd, v4, v5, left_odd, 0);
    split(v5, v5, v6, right_odd - left_odd + 1, 0);
    merge(even, v1, v5);
    merge(even, even, v3);
    merge(odd, v4, v2);
    merge(odd, odd, v6);
}

long long get_sum(Node *&v, int left, int right) {
    Node *v1, *v2, *v3;
    split(v, v1, v2, left, 0);
    split(v2, v2, v3, right - left + 1, 0);
    long long answer = get_sum(v2);
    merge(v, v1, v2);
    merge(v, v, v3);
    return answer;
}

long long get_sum(Node *&even, Node *&odd, int left, int right) {
    if (left == right) {
        return get_sum(left % 2 == 0 ? even : odd, left / 2, right / 2);
    }
    int left_even = (left + 1) / 2;
    int right_even = right / 2;
    int left_odd = left / 2;
    int right_odd = (right - 1) / 2;
    return get_sum(even, left_even, right_even) + get_sum(odd, left_odd, right_odd);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n, m, value, operation, left, right, count = 0;
    std::vector<int> even;
    std::vector<int> odd;
    while (true) {
        even.clear();
        odd.clear();
        Node *rootEven, *rootOdd;
        std::cin >> n >> m;
        if (n == 0 && m == 0) {
            break;
        }
        count++;
        if (count > 1) {
            std::cout << '\n';
        }
        std::cout << "Swapper " << count << ":" << '\n';
        for (int i = 0; i < n; ++i) {
            std::cin >> value;
            if (i % 2 == 0) {
                even.push_back(value);
            } else {
                odd.push_back(value);
            }
        }
        rootEven = create_Cartesian_Tree(even);
        rootOdd = create_Cartesian_Tree(odd);
        for (; m > 0; --m) {
            std::cin >> operation >> left >> right;
            --left, --right;
            if (operation == 1) {
                swapper(rootEven, rootOdd, left, right);
            } else {
                std::cout << get_sum(rootEven, rootOdd, left, right) << '\n';
            }
        }
    }
    return 0;
}
