//
// Created by Aleksandr Kiriak on 20.05.2024.
//
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

struct Point {
    ll x, y;

    bool operator<(const Point& other) const {
        return y == other.y ? x < other.x : y < other.y;
    }
};

struct Vector {
    ll x, y;

    Vector(Point A, Point B) {
        this->x = B.x - A.x;
        this->y = B.y - A.y;
    }
};

ll skew_product(const Vector& A, const Vector& B) {
    return A.x * B.y - A.y * B.x;
}

ll sign(ll x) {
    if (x == 0) {
        return 0;
    }
    return x > 0 ? 1 : -1;
}

// Лежит ли точка P на прямой AB
bool is_point_on_line(const Point& A, const Point& B, const Point& P) {
    return ((P.x - A.x) * (B.y - A.y)) == ((P.y - A.y) * (B.x - A.x));
}

// Лежит ли точка P на луче AB
bool is_point_on_ray(const Point& A, const Point& B, const Point& P) {
    if (!is_point_on_line(A, B, P)) {
        return false;
    }
    return (P.x - A.x) * (B.x - A.x) >= 0 && (P.y - A.y) * (B.y - A.y) >= 0;
}

// Лежит ли точка P в углу AOB (включая его стороны: лучи OA и OB)
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

// Лежит ли точка P в треугольнике ABC (включая его стороны)
bool is_point_in_triangle(const Point& A, const Point& B, const Point& C, const Point& P) {
    return is_point_in_angle(A, B, C, P) && is_point_in_angle(A, C, B, P) && is_point_in_angle(B, A, C, P);
}

// Лежит ли точка P в выпуклом многоугольнике (включая его стороны). Точки многоугольника даны в порядке обхода против часовой стрелки. O(log n)
bool is_point_in_polygon(const vector<Point>& polygon, const Point& P) {
    if (polygon.size() < 3) {
        return false;
    }
    if (!is_point_in_angle(polygon.back(), polygon.front(), polygon[1], P)) {
        return false;
    }
    int left = 1;
    int right = (int) polygon.size() - 1;
    while (left + 1 != right) {
        int mid = (right + left) / 2;
        if (is_point_in_angle(polygon.back(), polygon.front(), polygon[mid], P)) {
            left = mid;
        } else {
            right = mid;
        }
    }
    return is_point_in_triangle(polygon[right], polygon.front(), polygon[left], P);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<Point> polygon(n);
    for (int i = 0; i < n; i++) {
        cin >> polygon[i].x >> polygon[i].y;
    }

    int count = 0;
    Point missile{};
    for (int i = 0; i < m; i++) {
        cin >> missile.x >> missile.y;
        if (is_point_in_polygon(polygon, missile)) {
            count++;
        }
    }

    cout << (count >= k ? "YES" : "NO") << endl;
}
