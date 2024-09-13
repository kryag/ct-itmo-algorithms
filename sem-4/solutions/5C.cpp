//
// Created by Aleksandr Kiriak on 18.05.2024.
//
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct Point {
    ll x, y;
};

struct Vector {
    ll x, y;

    Vector(Point A, Point B) {
        this->x = B.x - A.x;
        this->y = B.y - A.y;
    }
};

// Знак числа
ll sign(ll x) {
    if (x == 0LL) {
        return 0LL;
    }
    return x > 0LL ? 1LL : -1LL;
}

// Скалярное произведение
ll scalar_product(const Vector& A, const Vector& B) {
    return A.x * B.x + A.y * B.y;
}

// Косое произведение
ll skew_product(const Vector& A, const Vector& B) {
    return A.x * B.y - A.y * B.x;
}

// Лежит ли точка P на отрезке AB
bool is_point_on_line_segment(const Point& A, const Point& B, const Point& P) {
    return sign(skew_product({A, B}, {A, P})) == 0 && sign(scalar_product({A, P}, {B, P})) <= 0;
}

// Множество точек пересечения отрезков AB и CD
vector<vector<double>> intersection_line_segments(const Point& A, const Point& B, const Point& C, const Point& D) {
    vector<vector<double>> result;
    if (is_point_on_line_segment(A, B, C)) {
        result.push_back({(double) C.x, (double) C.y});
    }
    if (is_point_on_line_segment(A, B, D)) {
        result.push_back({(double) D.x, (double) D.y});
    }
    if (is_point_on_line_segment(C, D, A)) {
        result.push_back({(double) A.x, (double) A.y});
    }
    if (is_point_on_line_segment(C, D, B)) {
        result.push_back({(double) B.x, (double) B.y});
    }
    if (!result.empty()) {
        return result;
    }
    if ((sign(skew_product({A, B}, {A, C})) * sign(skew_product({A, B}, {A, D})) < 0) &&
        (sign(skew_product({C, D}, {C, A})) * sign(skew_product({C, D}, {C, B})) < 0)) {
        ll A1 = B.y - A.y, B1 = A.x - B.x, C1 = A.y * B.x - A.x * B.y;
        ll A2 = D.y - C.y, B2 = C.x - D.x, C2 = C.y * D.x - C.x * D.y;
        double x = (double) (C2 * B1 - C1 * B2) / (double) (A1 * B2 - A2 * B1);
        double y = (double) (A2 * C1 - A1 * C2) / (double) (A1 * B2 - A2 * B1);
        result.push_back({x, y});
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll x, y;
    cin >> x >> y;
    Point A{x, y};
    cin >> x >> y;
    Point B{x, y};
    cin >> x >> y;
    Point C{x, y};
    cin >> x >> y;
    Point D{x, y};

    auto result = intersection_line_segments(A, B, C, D);
    if (result.empty()) {
        cout << "Empty" << endl;
    } else {
        sort(result.begin(), result.end(), [](const auto& a, const auto& b) {
            if (a[0] == b[0]) {
                return a[1] < b[1];
            }
            return a[0] < b[0];
        });
        cout << fixed << setprecision(10);
        cout << result[0][0] << ' ' << result[0][1] << endl;
        for (int i = 1; i < (int) result.size(); i++) {
            if (result[i][0] != result[i - 1][0] || result[i][1] != result[i - 1][1]) {
                cout << result[i][0] << ' ' << result[i][1] << endl;
            }
        }
    }
}
