//
// Created by Aleksandr Kiriak on 19.05.2024.
//
#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std;

typedef long long ll;

double distance(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

vector<double> circles_inter(double x0, double y0, double x1, double y1, double r0, double r1) {
    double d = distance(x0, y0, x1, y1);
    double a = (r0 * r0 - r1 * r1 + d * d) / (2 * d);
    double h = sqrt(r0 * r0 - a * a);
    double x2 = x0 + a * (x1 - x0) / d;
    double y2 = y0 + a * (y1 - y0) / d;
    double x3 = x2 + h * (y1 - y0) / d;
    double y3 = y2 - h * (x1 - x0) / d;
    double x4 = x2 - h * (y1 - y0) / d;
    double y4 = y2 + h * (x1 - x0) / d;
    return {x3, y3, x4, y4};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll x0, y0, r, x1, y1;
    cin >> x0 >> y0 >> r >> x1 >> y1;

    ll d_sqr = (x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1);
    if (d_sqr < r * r) {
        cout << 0 << endl;
        return 0;
    }
    if (d_sqr == r * r) {
        cout << 1 << endl;
        cout << x1 << ' ' << y1 << endl;
        return 0;
    }

    double d = sqrt(d_sqr);
    double mid_x = (double) (x0 + x1) / 2;
    double mid_y = (double) (y0 + y1) / 2;
    double r2 = d / 2;
    auto intersection = circles_inter(x0, y0, mid_x, mid_y, r, r2);
    double x21 = intersection[0], y21 = intersection[1], x22 = intersection[2], y22 = intersection[3];
    double x3 = (x21 + x22) / 2;
    double y3 = (y21 + y22) / 2;
    double d13 = distance(x1, y1, x3, y3);
    double d23 = distance(x21, y21, x3, y3);

    cout << 2 << endl;
    cout << fixed << setprecision(10);
    cout << x3 << ' ' << y3 << endl;
    cout << d13 << ' ' << d23 << endl;
    cout << x21 << ' ' << y21 << endl;
    cout << x22 << ' ' << y22 << endl;
}
