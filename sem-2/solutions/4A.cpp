#include <algorithm>
#include <iostream>
#include <vector>

const int SIZE = 2'540'313;

struct Cell {
    std::vector<int> v;

    bool exists(int x) {
        return std::find(v.begin(), v.end(), x) != v.end();
    }

    void insert(int x) {
        if (!exists(x)) {
            v.push_back(x);
        }
    }

    void remove(int x) {
        auto it = std::find(v.begin(), v.end(), x);
        if (it != v.end()) {
            v.erase(it);
        }
    }
};

int h(int x) {
    return std::abs(x) % SIZE;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::vector<Cell> a(SIZE);
    for (int i = 1; i <= SIZE; i++) {
        a.emplace_back();
    }
    std::string command;
    int value;
    while (std::cin >> command >> value) {
        if (command == "insert") {
            a[h(value)].insert(value);
        } else if (command == "delete") {
            a[h(value)].remove(value);
        } else {
            bool ans = a[h(value)].exists(value);
            if (ans) {
                std::cout << "true" << '\n';
            } else {
                std::cout << "false" << '\n';
            }
        }
    }
}
