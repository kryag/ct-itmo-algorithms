//
// Created by Aleksandr Kiriak on 24.05.2024.
//
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

struct Point {
    ll x, y;

    bool operator<(const Point& other) const {
        return y == other.y ? x < other.x : y < other.y;
    }

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Point& other) const {
        return !(*this == other);
    }
};

struct Vector {
    ll x, y;

    Vector(const Point& A, const Point& B) {
        this->x = B.x - A.x;
        this->y = B.y - A.y;
    }
};

ll sign(ll x) {
    if (x == 0) {
        return 0;
    }
    return x > 0 ? 1 : -1;
}

ll skew_product(const Vector& A, const Vector& B) {
    return A.x * B.y - A.y * B.x;
}

ll scalar_product(const Vector& A, const Vector& B) {
    return A.x * B.x + A.y * B.y;
}

ll dist_sqr(const Point& A, const Point& B) {
    ll dx = A.x - B.x;
    ll dy = A.y - B.y;
    return dx * dx + dy * dy;
}

// Лежит ли точка P на отрезке AB
bool is_point_on_line_segment(const Point& A, const Point& B, const Point& P) {
    return sign(skew_product({A, B}, {A, P})) == 0 && sign(scalar_product({A, P}, {B, P})) <= 0;
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

// Алгоритм Грэхэма, строящий выпуклую оболочку за O(nlogn).
vector<Point> convex_hull(vector<Point>& points) {
    int n = (int) points.size();

    Point start{};
    for (int i = 0; i < n; i++) {
        if (i == 0 || points[i] < start) {
            start = points[i];
        }
    }

    sort(points.begin(), points.end(), [&](const auto& a, const auto& b) {
        ll skew = sign(skew_product({start, a}, {start, b}));
        if (skew == 0) {
            return dist_sqr(start, a) > dist_sqr(start, b);
        }
        return skew > 0;
    });

    vector<Point> good_points;
    good_points.push_back(start);
    for (auto const& p : points) {
        if (p != start && good_points.back() != p && (good_points.size() == 1 || !is_point_on_line(start, good_points.back(), p))) {
            good_points.push_back(p);
        }
    }

    vector<Point> polygon;
    for (auto point : good_points) {
        while (polygon.size() >= 2 && skew_product({polygon[polygon.size() - 2], polygon.back()}, {polygon.back(), point}) <= 0) {
            polygon.pop_back();
        }
        polygon.push_back(point);
    }

    return polygon;
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

    int n;
    cin >> n;

    Point Ivan{};
    cin >> Ivan.x >> Ivan.y;

    vector<Point> lions(n);
    for (int i = 0; i < n; i++) {
        cin >> lions[i].x >> lions[i].y;
    }

    lions = convex_hull(lions);
    int size = (int) lions.size();

    for (int i = 0; i < size; i++) {
        if (Ivan == lions[i]) {
            cout << "NO" << endl;
            return 0;
        }
    }

    for (int i = 0; i < size; i++) {
        if (is_point_on_line_segment(lions[i], lions[(i + 1) % size], Ivan)) {
            cout << "YES" << endl;
            return 0;
        }
    }

    cout << (is_point_in_polygon(lions, Ivan) ? "NO" : "YES") << endl;
}
