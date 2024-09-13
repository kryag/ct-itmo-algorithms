//
// Created by Aleksandr Kiriak on 24.05.2024.
//
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

typedef long long ll;

const double PI = 3.14159265358979323846;

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

ll dist_sqr(const Point& A, const Point& B) {
    ll dx = A.x - B.x;
    ll dy = A.y - B.y;
    return dx * dx + dy * dy;
}

// Лежит ли точка P на прямой AB
bool is_point_on_line(const Point& A, const Point& B, const Point& P) {
    return ((P.x - A.x) * (B.y - A.y)) == ((P.y - A.y) * (B.x - A.x));
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, L;
    cin >> N >> L;

    vector<Point> castle(N);
    for (int i = 0; i < N; i++) {
        cin >> castle[i].x >> castle[i].y;
    }

    castle = convex_hull(castle);
    int size = (int) castle.size();
    double result = 0.0;
    for (int i = 0; i < size; i++) {
        result += sqrt(dist_sqr(castle[i], castle[(i + 1) % size]));
    }
    result += 2 * PI * L;

    cout << fixed << setprecision(10);
    cout << result << endl;
}
