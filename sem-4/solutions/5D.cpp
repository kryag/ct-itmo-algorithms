//
// Created by Aleksandr Kiriak on 18.05.2024.
//
#include <bits/stdc++.h>

using namespace std;

const long double EPS = 0.000'001;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    long double x, y, r, a, b, c;
    cin >> x >> y >> r >> a >> b >> c;

    long double x_a, y_a;
    if (abs(a) < EPS) {
        x_a = 0.0;
        y_a = -c / b;
    } else {
        x_a = -c / a;
        y_a = 0.0;
    }
    x_a -= x;
    y_a -= y;
    c = -(a * x_a + b * y_a);

    long double x0 = -a * c / (a * a + b * b);
    long double y0 = -b * c / (a * a + b * b);
    cout << fixed << setprecision(6);
    if (c * c > r * r * (a * a + b * b) + EPS) {
        cout << 0 << endl;
    } else if (abs(c * c - r * r * (a * a + b * b)) < EPS) {
        cout << 1 << endl;
        cout << x0 + x << ' ' << y0 + y << endl;
    } else {
        long double temp = sqrt((r * r - c * c / (a * a + b * b)) / (a * a + b * b));
        cout << 2 << endl;
        cout << x0 + b * temp + x << ' ' << y0 - a * temp + y << endl;
        cout << x0 - b * temp + x << ' ' << y0 + a * temp + y << endl;
    }
}
