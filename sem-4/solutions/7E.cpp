//
// Created by Aleksandr Kiriak on 30.05.2024.
//
#include <iostream>

using namespace std;

int main() {
    long long p;
    cin >> p;
    cout << ((p * (p - 1) / 2) % p) << endl;
}
