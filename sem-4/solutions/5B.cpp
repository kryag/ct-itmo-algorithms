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

ll sign(ll x) {
    if (x == 0LL) {
        return 0LL;
    }
    return x > 0LL ? 1LL : -1LL;
}

ll skew_product(const Vector& A, const Vector& B) {
    return A.x * B.y - A.y * B.x;
}

// принадлежит ли точка P лучу AB
bool is_point_on_ray(const Point& A, const Point& B, const Point& P) {
    bool on_line = (P.x - A.x) * (B.y - A.y) == (B.x - A.x) * (P.y - A.y);
    if (!on_line) {
        return false;
    }
    return (P.x - A.x) * (B.x - A.x) >= 0 && (P.y - A.y) * (B.y - A.y) >= 0;
}

// принадлежит ли точка P углу AOB (включая его стороны: лучи OA и OB)
bool is_point_in_angle(const Point& A, const Point& O, const Point& B, const Point& P) {
    if (is_point_on_ray(O, A, P) || is_point_on_ray(O, B, P)) {
        return true;
    }
    Vector OA = {O, A};
    Vector OP = {O, P};
    Vector OB = {O, B};
    return sign(skew_product(OA, OP)) * sign(skew_product(OA, OB)) > 0 &&
           sign(skew_product(OB, OP)) * sign(skew_product(OB, OA)) > 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll x, y;
    cin >> x >> y;
    Point A{x, y};
    cin >> x >> y;
    Point O{x, y};
    cin >> x >> y;
    Point B{x, y};
    cin >> x >> y;
    Point P{x, y};

    cout << (is_point_in_angle(A, O, B, P) ? "YES" : "NO") << endl;
}
