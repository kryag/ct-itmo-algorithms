#include <iostream>
#include <vector>

using namespace std;

struct Trie {
    struct Node {
        int count_term;
        Node* parent;
        pair<Node*, Node*> link;

        explicit Node(Node* parent) : count_term(0), parent(parent) {}

        Node*& get(bool bit) {
            return bit ? link.second : link.first;
        }

        void set(bool bit, Node* node) {
            get(bit) = node;
        }
    };

    static constexpr int BIT_SIZE = 32;
    Node* root;

    explicit Trie() : root(new Node(nullptr)) {}

    void insert(int x) {
        auto v = get_node(x);
        v->count_term++;
    }

    void remove(int x) {
        auto v = get_node(x);
        if (!--v->count_term) {
            while (is_leaf(v)) {
                Node* vrm = v;
                v = v->parent;
                v->set(v->link.second == vrm, nullptr);
                delete vrm;
            }
        }
    }

    int max_xor(int x) const {
        auto binary_x = to_binary(x);
        Node* v = root;
        vector<bool> res(BIT_SIZE);
        for (int i = BIT_SIZE - 1; i >= 0; i--) {
            bool bit = binary_x[i];
            res[i] = v->get(!bit);
            v = v->get(res[i] ? !bit : bit);
        }
        return to_int(res);
    }

    Node* get_node(int x) {
        auto binary_x = to_binary(x);
        Node* v = root;
        for (int i = BIT_SIZE - 1; i >= 0; i--) {
            bool bit = binary_x[i];
            if (!v->get(bit)) {
                v->set(bit, new Node(v));
            }
            v = v->get(bit);
        }
        return v;
    }

    bool is_leaf(Node* v) const {
        return v && v != root && !v->get(false) && !v->get(true);
    }

    static vector<bool> to_binary(int x) {
        vector<bool> res(BIT_SIZE);
        for (int i = 0; i < BIT_SIZE; i++) {
            res[i] = 1 & (x >> i);
        }
        return res;
    }

    static int to_int(vector<bool> const& v) {
        int res = 0;
        for (int i = 0; i < BIT_SIZE; i++) {
            if (v[i]) {
                res += 1 << i;
            }
        }
        return res;
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Trie trie;
    trie.insert(0);

    int q;
    cin >> q;

    for (int i = 0; i < q; i++) {
        char command;
        int x;
        cin >> command >> x;
        if (command == '+') {
            trie.insert(x);
        } else if (command == '-') {
            trie.remove(x);
        } else {
            cout << trie.max_xor(x) << '\n';
        }
    }
}
