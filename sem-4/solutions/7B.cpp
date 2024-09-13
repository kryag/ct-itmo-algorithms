//
// Created by Aleksandr Kiriak on 03.06.2024.
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

pair<bool, pair<ll, ll>> solve_diophantine_equation(ll a, ll b, ll c) {
    auto res = gcd(a, b);
    ll d = res[0], x = res[1], y = res[2];

    if (c % d != 0) {
        return {false, {}};
    }

    ll k1 = c / d * x;
    ll k2 = b / d;
    pair<ll, ll> ans;
    if (k1 > 0) {
        ll tmp = -(k1 / k2);
        ans = {k1 + k2 * tmp, c / d * y - a / d * tmp};
    } else if (k1 < 0) {
        ll tmp = -((k1 - k2 + 1) / k2);
        ans = {k1 + k2 * tmp, c / d * y - a / d * tmp};
    } else {
        ans = {0, c / d * y};
    }

    return {true, ans};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        ll a, b, n, m;
        cin >> a >> b >> n >> m;
        auto result = solve_diophantine_equation(n, -m, b - a);
        if (!result.first) {
            cout << "NO" << endl;
        } else {
            ll p = (n * m) / gcd(n, m)[0];
            ll x0 = a + result.second.first * n;
            x0 = (x0 + p * (abs(x0) / p + 1)) % p;
            cout << "YES " << x0 << ' ' << p << endl;
        }
    }
}
