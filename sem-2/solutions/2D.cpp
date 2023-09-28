#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> alf[26];

int set(int q, int ql, int qr, int delta) {
    if (alf[q].empty()) {
        return delta;
    }
    int left = std::lower_bound(alf[q].data(), alf[q].data() + alf[q].size(), ql) - alf[q].data();
    int right = std::upper_bound(alf[q].data(), alf[q].data() + alf[q].size(), qr) - alf[q].data();
    for (int i = left; i < right; i++) {
        alf[q][i] = delta;
        delta++;
    }
    return delta;
}

int main() {
    int n, q;
    std::cin >> n >> q;
    std::string s;
    std::cin >> s;
    for (int i = 0; i < s.length(); i++) {
        int c = s[i] - 'a';
        alf[c].push_back(i);
    }
    for (int i = 0; i < q; i++) {
        int ql, qr, k;
        std::cin >> ql >> qr >> k;
        ql--;
        qr--;
        int delta = ql;
        if (k == 1) {
            for (int no = 0; no < 26; no++) {
                delta = set(no, ql, qr, delta);
            }
        } else {
            for (int no = 25; no >= 0; no--) {
                delta = set(no, ql, qr, delta);
            }
        }
    }
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < alf[i].size(); j++) {
            s[alf[i][j]] = 'a' + i;
        }
    }
    std::cout << s;
    return 0;
}
