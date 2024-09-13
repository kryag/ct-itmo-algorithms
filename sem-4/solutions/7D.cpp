//
// Created by Aleksandr Kiriak on 30.05.2024.
//
#include <iostream>
#include <vector>

using namespace std;

int p, sz;
vector<int> rec;

int get_rec(int number) {
    if (number < sz) {
        return rec[number];
    }
    return (p - (long long) (p / number) * get_rec(p % number) % p) % p;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> p;
    sz = p < 10 ? p : p / 5;
    rec.resize(sz);

    rec[1] = 1;
    for (int i = 2; i < sz; i++) {
        rec[i] = (p - (long long) (p / i) * rec[p % i] % p) % p;
    }

    int sum = 0, count = 0;
    for (int i = 1; i < p; i++) {
        sum = (sum + get_rec(i)) % p;
        count++;
        if (count == 100 || i == p - 1) {
            cout << sum << ' ';
            sum = 0;
            count = 0;
        }
    }
}
