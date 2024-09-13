//
// Created by Aleksandr Kiriak on 29.05.2024.
//
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

vector<ll> gcd(ll a, ll b) {
    if (b == 0) {
        return {a, 1, 0};
    }
    auto ans = gcd(b, a % b);
    return {ans[0], ans[2], ans[1] - (a / b) * ans[2]};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll a, b, c;
    cin >> a >> b >> c;

    auto res = gcd(a, b);
    ll d = res[0], x = res[1], y = res[2];

    if (c % d != 0) {
        cout << "Impossible" << endl;
        return 0;
    }

    ll k1 = c / d * x;
    ll k2 = b / d;
    if (k1 > 0) {
        ll tmp = -(k1 / k2);
        cout << k1 + k2 * tmp << " " << c / d * y - a / d * tmp << endl;
    } else if (k1 < 0) {
        ll tmp = -((k1 - k2 + 1) / k2);
        cout << k1 + k2 * tmp << " " << c / d * y - a / d * tmp << endl;
    } else {
        cout << 0 << " " << c / d * y << endl;
    }
}
