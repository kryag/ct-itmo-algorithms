//
// Created by Aleksandr Kiriak on 30.05.2024.
//
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int p;
    cin >> p;

    vector<int> rec(p);
    rec[1] = 1;
    for (int i = 2; i < p; i++) {
        rec[i] = (p - (long long) (p / i) * rec[p % i] % p) % p;
    }
    for (int i = 1; i < p; i += 100) {
        int sum = 0;
        for (int j = i; j < min(i + 100, p); j++) {
            sum = (sum + rec[j]) % p;
        }
        cout << sum << ' ';
    }
    cout << endl;
}
