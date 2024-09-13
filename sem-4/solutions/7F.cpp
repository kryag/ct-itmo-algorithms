//
// Created by Aleksandr Kiriak on 03.06.2024.
//
#pragma GCC optimize("O3,unroll-loops")
#include <iostream>
#include <vector>
#include <random>

using namespace std;

typedef unsigned long long ull;
typedef __uint128_t ui128;

random_device rd;
mt19937 gen(rd());
ull power2[64];

void calculate() {
    power2[0] = 1;
    for (int i = 1; i <= 63; ++i) {
        power2[i] = 2 * power2[i - 1];
    }
}

ull gcd(ull a, ull b) {
    if (a < b) {
        swap(a, b);
    }
    while (b != 0) {
        ull tmp = a;
        a = b;
        b = tmp % b;
    }
    return a;
}

ull pow(ull x, ull p, ull mod) {
    ull result = 1;
    while (p) {
        if (p & 1) {
            result = ((ui128) result * x) % mod;
        }
        x = ((ui128) x * x) % mod;
        p >>= 1;
    }
    return result;
}

bool Miller_Rabin(ull number) {
    if (number == 1 || (number % 2 == 0 && number > 2)) {
        return false;
    }
    ull zeroes = 0;
    ull tmp = number - 1;
    while (tmp % 2 == 0) {
        tmp /= 2;
        zeroes++;
    }
    uniform_int_distribution<ull> distrib(1, number - 1);
    for (int _ = 0; _ < 5; ++_) {
        ull a = distrib(gen);
        bool check1 = pow(a, tmp, number) == 1;
        if (check1) {
            continue;
        }
        bool check2 = false;
        for (ull z = 0; z < zeroes; z++) {
            if (pow(a, ((ui128) power2[z] * tmp) % number, number) == number - 1) {
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

ull Pollard_Rho(ull n, ull max_step = 100'000) {
    if (n == 4) {
        return 2;
    }
    ull i = 1;
    uniform_int_distribution<ull> distrib(0, n - 1);
    ull x = distrib(gen);
    ull y = x;
    ull k = 2;
    while (true) {
        i++;
        x = ((ui128) x * x - 1 + n) % n;
        ull d = gcd(y - x, n);
        if (d != 1 && d != n) {
            return d;
        }
        if (i == k) {
            y = x;
            k *= 2;
        }
        if (i == max_step) {
            return Pollard_Rho(n);
        }
    }
}

vector<ull> factorization(ull n) {
    if (n == 1 || Miller_Rabin(n)) {
        return {n};
    }

    ull d = Pollard_Rho(n);
    auto d_fact = factorization(d);
    auto n_rest_fact = factorization(n / d);
    n_rest_fact.insert(n_rest_fact.end(), d_fact.begin(), d_fact.end());

    return n_rest_fact;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ull n;
    cin >> n;

    calculate();
    auto factor = factorization(n - 1);
    cout << factor.size() << endl;
    for (ull x : factor) {
        cout << x - 1 << ' ';
    }
    cout << endl;
}
