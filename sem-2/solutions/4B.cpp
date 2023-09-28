#include <iostream>
#include <utility>
#include <vector>

const int SIZE = 1'302'331;

struct Node {
    std::string key;
    std::string value;
    Node *next;
    Node *prev;

    Node(std::string key, std::string value, Node *next, Node *prev) :
            key(std::move(key)), value(std::move(value)), next(next), prev(prev) {};

    void change(std::string newKey, std::string newValue, Node *newNext, Node *newPrev) {
        this->key = std::move(newKey);
        this->value = std::move(newValue);
        this->next = newNext;
        this->prev = newPrev;
    }
};

std::vector<std::vector<Node>> map(SIZE);

int h(const std::string &s) {
    int sum = 0;
    for (char i: s) {
        sum += (53 * sum + i);
        sum %= SIZE;
    }
    return sum;
}

std::string get(const std::string &key, int hash) {
    for (auto &i: map[hash]) {
        if (i.key == key) {
            return i.value;
        }
    }
    return "none";
}

std::string prevOrNext(const std::string &key, int hash, bool flag) { // flag: true = prev, false = next
    for (auto &i: map[hash]) {
        if (i.key == key) {
            if (flag) {
                if (i.prev != nullptr) {
                    return i.prev->value;
                }
            } else {
                if (i.next != nullptr) {
                    return i.next->value;
                }
            }
        }
    }
    return "none";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string command, key, value;
    Node *prev = nullptr;
    while (std::cin >> command >> key) {
        int hash = h(key) % SIZE;
        bool flag = false;
        if (command == "put") {
            std::cin >> value;
            for (auto &i: map[hash]) {
                if (i.key == key) {
                    flag = true;
                    i.value = value;
                }
            }
            if (!flag) {
                if (map[hash].empty()) {
                    map[hash].reserve(10);
                }
                Node x(key, value, nullptr, prev);
                map[hash].push_back(x);
                if (prev != nullptr) {
                    prev->next = &map[hash][map[hash].size() - 1];
                }
                prev = &map[hash][map[hash].size() - 1];
            }
        } else if (command == "delete") {
            for (auto &i: map[hash]) {
                if (i.key == key) {
                    if (i.next == nullptr) {
                        prev = i.prev;
                    } else {
                        i.next->prev = i.prev;
                    }
                    if (i.prev != nullptr) {
                        i.prev->next = i.next;
                    }
                    i.change("", "", nullptr, nullptr);
                    break;
                }
            }
        } else if (command == "get") {
            std::cout << get(key, hash) << '\n';
        } else if (command == "prev") {
            std::cout << prevOrNext(key, hash, true) << '\n';
        } else {
            std::cout << prevOrNext(key, hash, false) << '\n';
        }
    }
    return 0;
}
