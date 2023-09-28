#include <iostream>
#include <random>
#include <unordered_set>
#include <vector>

int p, q;
std::random_device rd;
std::mt19937 gen(rd());

char random_char() {
    std::uniform_int_distribution<> dist(97, 122);
    return (char) dist(gen);
}

long long get_hash(const std::string &s, int cur) {
    if (cur == -1) {
        return 0;
    }
    return (get_hash(s, cur - 1) * p + s[cur]) % q;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::cin >> p >> q;
    std::unordered_set<int> set;
    std::vector<std::pair<int, std::string>> v;
    while (true) {
        std::string s;
        for (int i = 0; i < 100; i++) {
            s.push_back(random_char());
        }
        int cur_hash = get_hash(s, s.length() - 1);
        if (set.count(cur_hash) == 0) {
            set.insert(cur_hash);
            v.emplace_back(cur_hash, s);
        } else {
            bool flag = false;
            for (auto &i: v) {
                if (i.first == cur_hash && i.second != s) {
                    std::cout << s << '\n' << i.second;
                    flag = true;
                    break;
                }
            }
            if (flag) {
                break;
            }
        }
    }
    return 0;
}
