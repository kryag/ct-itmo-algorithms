//
// Created by Aleksandr Kiriak on 03.06.2024.
//
#pragma GCC optimize("O3,unroll-loops")
#include <iostream>
#include <ctime>

using namespace std;

typedef long long ll;

ll power2[64];

void calculate() {
    power2[0] = 1;
    for (int i = 1; i <= 63; ++i) {
        power2[i] = 2 * power2[i - 1];
    }
}

ll multiply(ll x, ll y, ll mod) {
    ll result = 0;
    while (y) {
        if (y & 1) {
            result = (result + x) % mod;
        }
        x = (x * 2) % mod;
        y >>= 1;
    }
    return result;
}

ll pow(ll x, ll p, ll mod) {
    ll result = 1;
    while (p) {
        if (p & 1) {
            result = multiply(result, x, mod);
        }
        x = multiply(x, x, mod);
        p >>= 1;
    }
    return result;
}

bool Miller_Rabin(ll number) {
    if (number == 1 || number % 2 == 0 && number > 2) {
        return false;
    }
    ll zeroes = 0;
    ll tmp = number - 1;
    while (tmp % 2 == 0) {
        tmp /= 2;
        zeroes++;
    }
    srand(time(nullptr));
    for (int _ = 0; _ < 4; ++_) {
        ll a = rand() % number;
        if (a == 0) {
            a++;
        }
        bool check1 = pow(a % number, tmp, number) == 1;
        if (check1) {
            continue;
        }
        bool check2 = false;
        for (int z = 0; z < zeroes; z++) {
            if (pow(a % number, multiply(power2[z], tmp, number), number) == number - 1) {
                check2 = true;
                break;
            }
        }
        if (!check2) {
            return false;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;

    calculate();
    while (n--) {
        ll number;
        cin >> number;
        cout << (Miller_Rabin(number) ? "YES" : "NO") << endl;
    }
}
