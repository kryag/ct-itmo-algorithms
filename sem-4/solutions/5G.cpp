//
// Created by Aleksandr Kiriak on 18.05.2024.
//
#include <iostream>

using namespace std;

typedef long long ll;

struct Point {
    ll x, y;
};

struct Vector {
    Point A{}, B{};
    ll x, y;

    Vector(Point A, Point B) {
        this->A = A;
        this->B = B;
        this->x = B.x - A.x;
        this->y = B.y - A.y;
    }
};

ll scalar_product(const Vector& A, const Vector& B) {
    return A.x * B.x + A.y * B.y;
}

bool is_point_on_line(const Point& A, const Point& B, const Point& P) {
    return ((P.x - A.x) * (B.y - A.y)) == ((P.y - A.y) * (B.x - A.x));
}

ll angle_between(const Vector& a, const Vector& b) {
    ll scalar = scalar_product(a, b);
    if (scalar == 0) {
        return 0;
    }
    if (is_point_on_line(a.A, a.B, b.A) && is_point_on_line(a.A, a.B, b.B)) {
        return scalar > 0 ? 2 : -2;
    }
    return scalar > 0 ? 1 : -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    Point prev_point{0, 0};
    Vector prev_vector(prev_point, {1, 0});
    for (int i = 0; i < n; i++) {
        Point cur_point{};
        cin >> cur_point.x >> cur_point.y;

        Vector cur_vector(prev_point, cur_point);
        Vector prev_vector_rot{prev_vector.A, {prev_vector.A.x - prev_vector.y, prev_vector.A.y + prev_vector.x}};

        ll angle = angle_between(prev_vector, cur_vector);
        ll angle_rot = angle_between(prev_vector_rot, cur_vector);

        prev_vector = cur_vector;
        prev_point = cur_point;

        if (angle == 2) {
            cout << "F ";
            continue;
        }
        if (angle == -2) {
            cout << "B ";
            continue;
        }
        if (angle_rot >= 1) {
            if (angle == 0) {
                cout << "L ";
            } else if (angle == 1) {
                cout << "LF ";
            } else {
                cout << "LB ";
            }
        } else {
            if (angle == 0) {
                cout << "R ";
            } else if (angle == 1) {
                cout << "RF ";
            } else {
                cout << "RB ";
            }
        }
    }
    cout << endl;
}
