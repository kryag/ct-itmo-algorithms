//
// Created by Aleksandr Kiriak on 19.05.2024.
//
#pragma GCC optimize("Ofast")
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

typedef long long ll;

const int MAX_N = 7000;

ll sqr_dist_point_to_point(int x1, int y1, int x2, int y2) {
    return (ll) (x1 - x2) * (x1 - x2) + (ll) (y1 - y2) * (y1 - y2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    int x[MAX_N], y[MAX_N];
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }

    ll result = 0;
    for (int i = 0; i < n - 1; i++) {
        int xi = x[i];
        int yi = y[i];
        for (int j = i + 1; j < n; j++) {
            result = max(result, sqr_dist_point_to_point(xi, yi, x[j],y[j]));
        }
    }

    cout << fixed << setprecision(20);
    cout << sqrt(result) << endl;
}
