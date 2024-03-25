#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct Trie {
    struct Node {
        int size;
        map<char, Node*> link;

        Node() : size(0) {}

        bool count(char c) {
            return link.count(c);
        }

        void set(char c, Node* node) {
            get(c) = node;
        }

        Node*& get(char c) {
            return link[c];
        }
    };

    Node* root;

    explicit Trie() : root(new Node()) {}

    long long count_substr(string const& s) {
        for (int i = 0; i < s.length(); i++) {
            insert(s.substr(i));
        }

        vector<vector<int>> count(s.length() + 1);
        dfs(root, count, 0);

        long long res = 0LL;
        for (auto const& v : count) {
            int sum = 0;
            for (int i = (int) v.size() - 1; i >= 0; i--) {
                res += sum * v[i];
                sum += v[i];
            }
        }
        return res;
    }

    void insert(string const& s) {
        Node* v = root;
        for (char c: s) {
            if (!v->count(c)) {
                v->set(c, new Node());
            }
            v = v->get(c);
            v->size++;
        }
    }

    void dfs(Node* v, vector<vector<int>>& count, int depth) {
        count[depth].push_back(v->size);
        for (auto const& [c, u] : v->link) {
            dfs(u, count, depth + 1);
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Trie trie;

    string s;
    cin >> s;
    cout << trie.count_substr(s) << '\n';
}
