//
// Created by Aleksandr Kiriak on 19.05.2024.
//
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const double EPS = 0.000'001;

struct Point {
    ll x, y;
};

struct Vector {
    ll x, y;
    double length;

    Vector(Point A, Point B) {
        this->x = B.x - A.x;
        this->y = B.y - A.y;
        this->length = sqrt(x * x + y * y);
    }
};

// Знак числа
ll sign(ll x) {
    if (x == 0) {
        return 0;
    }
    return x > 0 ? 1 : -1;
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

// Лежит ли точка P на прямой AB
bool is_point_on_line(const Point& A, const Point& B, const Point& P) {
    return ((P.x - A.x) * (B.y - A.y)) == ((P.y - A.y) * (B.x - A.x));
}

// Пересекает ли отрезок AB отрезок CD
bool is_line_segment_intersects_line_segment(const Point& A, const Point& B, const Point& C, const Point& D) {
    if (is_point_on_line_segment(A, B, C) || is_point_on_line_segment(A, B, D) ||
        is_point_on_line_segment(C, D, A) || is_point_on_line_segment(C, D, B)) {
        return true;
    }
    return (sign(skew_product({A, B}, {A, C})) * sign(skew_product({A, B}, {A, D})) < 0) &&
           (sign(skew_product({C, D}, {C, A})) * sign(skew_product({C, D}, {C, B})) < 0);
}

// Пересекает ли отрезок AB прямую CD
bool is_line_segment_intersects_line(const Point& A, const Point& B, const Point& C, const Point& D) {
    return sign(skew_product({C, D}, {C, A})) * sign(skew_product({C, D}, {C, B})) <= 0;
}

// Пересекает ли отрезок AB луч CD
bool is_line_segment_intersects_ray(const Point& A, const Point& B, const Point& C, const Point& D) {
    if (!is_line_segment_intersects_line(A, B, C, D)) {
        return false;
    }
    if ((A.x == C.x && A.y == C.y) || (B.x == C.x && B.y == C.y)) {
        return true;
    }
    if (is_point_on_line(C, D, A) && is_point_on_line(C, D, B)) {
        return sign(scalar_product({C, D}, {C, A})) > 0 || sign(scalar_product({C, D}, {C, B})) > 0;
    }
    double x1 = A.x, y1 = A.y, x2 = B.x, y2 = B.y, x3 = C.x, y3 = C.y, x4 = D.x, y4 = D.y;
    double x = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) / ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));
    double y = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) / ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));
    if (abs(x - x3) <= EPS && abs(y - y3) <= EPS) {
        return true;
    }
    double scalar = ((x4 - x3) * (x - x3) + (y4 - y3) * (y - y3));
    return scalar >= EPS;
}

// Пересекает ли прямая AB прямую CD
bool is_line_intersects_line(const Point& A, const Point& B, const Point& C, const Point& D) {
    if (is_point_on_line(A, B, C) || is_point_on_line(A, B, D)) {
        return true;
    }
    return sign(skew_product({A, B}, {C, D})) != 0;
}

// Пересекает ли луч AB прямую CD
bool is_ray_intersects_line(const Point& A, const Point& B, const Point& C, const Point& D) {
    if (is_point_on_line(C, D, A) || is_point_on_line(C, D, B)) {
        return true;
    }
    if (!is_line_intersects_line(A, B, C, D)) {
        return false;
    }
    double x1 = A.x, y1 = A.y, x2 = B.x, y2 = B.y, x3 = C.x, y3 = C.y, x4 = D.x, y4 = D.y;
    double x = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) / ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));
    double y = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) / ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));
    double scalar = ((x2 - x1) * (x - x1) + (y2 - y1) * (y - y1));
    return scalar >= EPS;
}

// Пересекает ли луч AB луч CD
bool is_ray_intersects_ray(const Point& A, const Point& B, const Point& C, const Point& D) {
    if (A.x == C.x && A.y == C.y) {
        return true;
    }
    if (is_point_on_line(C, D, A) && is_point_on_line(C, D, B)) {
        return sign(scalar_product({A, B}, {C, D})) > 0 || sign(scalar_product({C, D}, {C, A})) > 0;
    }
    return is_ray_intersects_line(A, B, C, D) && is_ray_intersects_line(C, D, A, B);
}

// Расстояние от точки A до точки B
double dist_point_to_point(const Point& A, const Point& B) {
    ll dx = A.x - B.x;
    ll dy = A.y - B.y;
    return sqrt(dx * dx + dy * dy);
}

// Расстояние от точки P до прямой AB
double dist_point_to_line(const Point& A, const Point& B, const Point& P) {
    Vector AB(A, B);
    if (AB.x * AB.x + AB.y * AB.y == 0) {
        return 0.0;
    }
    return (double) abs(skew_product(AB, {A, P})) / AB.length;
}

// Расстояние от точки P до отрезка AB
double dist_point_to_line_segment(const Point& A, const Point& B, const Point& P) {
    if (sign(scalar_product({A, P}, {A, B})) >= 0 && sign(scalar_product({B, P}, {B, A})) >= 0) {
        return dist_point_to_line(A, B, P);
    }
    return min(dist_point_to_point(A, P), dist_point_to_point(B, P));
}

// Расстояние от точки P до луча AB
double dist_point_to_ray(const Point& A, const Point& B, const Point& P) {
    if (sign(scalar_product({A, P}, {A, B})) >= 0) {
        return dist_point_to_line(A, B, P);
    }
    return dist_point_to_point(A, P);
}

// Расстояние от отрезка AB до отрезка CD
double dist_line_segment_to_line_segment(const Point& A, const Point& B, const Point& C, const Point& D) {
    if (is_line_segment_intersects_line_segment(A, B, C, D)) {
        return 0.0;
    }
    return min(
            min(dist_point_to_line_segment(A, B, C), dist_point_to_line_segment(A, B, D)),
            min(dist_point_to_line_segment(C, D, A), dist_point_to_line_segment(C, D, B))
    );
}

// Расстояние от отрезка AB до луча CD
double dist_line_segment_to_ray(const Point& A, const Point& B, const Point& C, const Point& D) {
    if (is_line_segment_intersects_ray(A, B, C, D)) {
        return 0.0;
    }
    return min(
            min(dist_point_to_ray(C, D, A), dist_point_to_ray(C, D, B)),
            dist_point_to_line_segment(A, B, C)
    );
}

// Расстояние от отрезка AB до прямой CD
double dist_line_segment_to_line(const Point& A, const Point& B, const Point& C, const Point& D) {
    if (is_line_segment_intersects_line(A, B, C, D)) {
        return 0.0;
    }
    return min(dist_point_to_line(C, D, A), dist_point_to_line(C, D, B));
}

// Расстояние от луча AB до луча CD
double dist_ray_to_ray(const Point& A, const Point& B, const Point& C, const Point& D) {
    if (is_ray_intersects_ray(A, B, C, D)) {
        return 0.0;
    }
    return min(dist_point_to_ray(C, D, A), dist_point_to_ray(A, B, C));
}

// Расстояние от луча AB до прямой CD
double dist_ray_to_line(const Point& A, const Point& B, const Point& C, const Point& D) {
    if (is_ray_intersects_line(A, B, C, D)) {
        return 0.0;
    }
    return dist_point_to_line(C, D, A);
}

// Расстояние от прямой AB до прямой CD
double dist_line_to_line(const Point& A, const Point& B, const Point& C, const Point& D) {
    if (is_line_intersects_line(A, B, C, D)) {
        return 0.0;
    }
    return dist_point_to_line(A, B, C);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int x, y;
    cin >> x >> y;
    Point A{x, y};
    cin >> x >> y;
    Point B{x, y};
    cin >> x >> y;
    Point C{x, y};
    cin >> x >> y;
    Point D{x, y};

    cout << fixed << setprecision(10);

    cout << dist_point_to_point(A, C) << endl;
    cout << dist_point_to_line_segment(C, D, A) << endl;
    cout << dist_point_to_ray(C, D, A) << endl;
    cout << dist_point_to_line(C, D, A) << endl;

    cout << dist_point_to_line_segment(A, B, C) << endl;
    cout << dist_line_segment_to_line_segment(A, B, C, D) << endl;
    cout << dist_line_segment_to_ray(A, B, C, D) << endl;
    cout << dist_line_segment_to_line(A, B, C, D) << endl;

    cout << dist_point_to_ray(A, B, C) << endl;
    cout << dist_line_segment_to_ray(C, D, A, B) << endl;
    cout << dist_ray_to_ray(A, B, C, D) << endl;
    cout << dist_ray_to_line(A, B, C, D) << endl;

    cout << dist_point_to_line(A, B, C) << endl;
    cout << dist_line_segment_to_line(C, D, A, B) << endl;
    cout << dist_ray_to_line(C, D, A, B) << endl;
    cout << dist_line_to_line(A, B, C, D) << endl;
}
