#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct Trie {

    explicit Trie(vector<char> const& alphabet) : root(new Node), alphabet(alphabet) {}

    void insert(string const& s) {
        if (count(s)) {
            return;
        }
        Node* v = root;
        for (char c: s) {
            if (!(v->count(c))) {
                v->set(c, new Node());
            }
            v->count_term_subtree++;
            v = v->go(c);
        }
        v->count_term_subtree++;
        v->is_term = true;
    }

    bool count(string const& s) {
        Node *v = root;
        for (char c: s) {
            if (!(v->count(c))) {
                return false;
            }
            v = v->go(c);
        }
        return v->is_term;
    }

    string get_kth(int k) {
        Node* v = root;
        string s;
        while (k > 1 || !(v->is_term)) {
            k -= v->is_term;
            for (auto const& [c, node]: v->link) {
                if (node->count_term_subtree >= k) {
                    s += c;
                    v = node;
                    break;
                } else {
                    k -= node->count_term_subtree;
                }
            }
        }
        return s;
    }

private:
    struct Node {
        bool is_term;
        int count_term_subtree;
        map<char, Node*> link;

        Node() : is_term(false), count_term_subtree(0) {}

        bool count(char c) {
            return link.count(c);
        }

        void set(char c, Node* node) {
            link[c] = node;
        }

        Node* go(char c) {
            return link[c];
        }
    };

    Node* root;
    vector<char> alphabet;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<char> alphabet;
    for (char c = 'a'; c <= 'z'; c++) {
        alphabet.push_back(c);
    }

    Trie trie(alphabet);

    int n;
    cin >> n;

    while (n--) {
        int command;
        cin >> command;
        if (command == 1) {
            string s;
            cin >> s;
            trie.insert(s);
        } else {
            int k;
            cin >> k;
            cout << trie.get_kth(k) << '\n';
        }
    }
}
