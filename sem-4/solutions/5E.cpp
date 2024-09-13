//
// Created by Aleksandr Kiriak on 19.05.2024.
//
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

typedef long long ll;

double dist_point_to_point(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void solve() {
    ll x1, y1, r1, x2, y2, r2;
    cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;

    if (x1 == x2 && y1 == y2 && r1 == r2) {
        cout << 3 << endl;
        return;
    }

    ll d = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
    ll sum_r = (r1 + r2) * (r1 + r2);
    ll sub_r = (r1 - r2) * (r1 - r2);

    if (d < sub_r || d > sum_r) {
        cout << 0 << endl;
        return;
    }

    if (d == sum_r) {
        cout << 1 << endl;
        cout << x1 + (double) r1 * (x2 - x1) / (r1 + r2) << ' ' << y1 + (double) r1 * (y2 - y1) / (r1 + r2) << endl;
        return;
    }
    if (d == sub_r) {
        cout << 1 << endl;
        cout << x1 + (double) r1 * (x2 - x1) / (r1 - r2) << ' ' << y1 + (double) r1 * (y2 - y1) / (r1 - r2) << endl;
        return;
    }

    double d_sqrt = sqrt(d);
    double a = (double) (r1 * r1 - r2 * r2 + d) / (2 * d_sqrt);
    double H_x = x1 + a * (x2 - x1) / d_sqrt;
    double H_y = y1 + a * (y2 - y1) / d_sqrt;
    double h = sqrt(r1 * r1 - a * a);
    double P1_x = H_x + h * (y2 - y1) / d_sqrt;
    double P1_y = H_y - h * (x2 - x1) / d_sqrt;
    double P2_x = H_x - h * (y2 - y1) / d_sqrt;
    double P2_y = H_y + h * (x2 - x1) / d_sqrt;

    cout << 2 << endl;
    cout << H_x << ' ' << H_y << endl;
    cout << dist_point_to_point(x1, y1, H_x, H_y) << ' ' << dist_point_to_point(P1_x, P1_y, H_x, H_y) << endl;
    cout << P1_x << ' ' << P1_y << endl;
    cout << P2_x << ' ' << P2_y << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;

    cout << fixed << setprecision(10);
    while (t--) {
        solve();
    }
}
