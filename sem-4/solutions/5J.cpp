//
// Created by Aleksandr Kiriak on 20.05.2024.
//
#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

typedef long long ll;

struct Point {
    ll x, y;
    int index, next;

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

ll double_area(const vector<Point>& polygon) {
    ll result = 0;
    int size = (int) polygon.size();
    for (int i = 0; i < size; i++) {
        int next = (i + 1) % size;
        result += (polygon[next].y + polygon[i].y) * (polygon[next].x - polygon[i].x);
    }
    return abs(result);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    vector<Point> points;
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        int prev_size = (int) points.size();
        points.resize(prev_size + k);
        for (int j = 0; j < k; j++) {
            int index = prev_size + j;
            cin >> points[index].x >> points[index].y;
            points[index].index = index;
            points[index].next = index + 1;
        }
        points.back().next = prev_size;
    }

    int points_size = (int) points.size();
    sort(points.begin(), points.end());
    unordered_map<int, int> new_indexes;
    for (int i = 0; i < points_size; i++) {
        new_indexes[points[i].index] = i;
        points[i].index = i;
    }
    for (int i = 0; i < points_size; i++) {
        points[i].next = new_indexes[points[i].next];
    }

    vector<bool> mark(points_size);
    vector<vector<Point>> polygons;
    for (int i = 0; i < points_size; i++) {
        if (!mark[i]) {
            polygons.emplace_back();
            int cur = i;
            do {
                polygons.back().push_back(points[cur]);
                mark[cur] = true;
                cur = points[cur].next;
            } while (!mark[cur]);
        }
    }

    int m;
    cin >> m;

    int polygons_size = (int) polygons.size();
    vector<bool> capture(polygons_size);

    Point invader{};
    for (int i = 0; i < m; i++) {
        cin >> invader.x >> invader.y;
        if (!is_point_in_polygon(polygons[0], invader)) {
            continue;
        }
        int left = 0;
        int right = polygons_size;
        while (left + 1 != right) {
            int mid = (right + left) / 2;
            if (is_point_in_polygon(polygons[mid], invader)) {
                left = mid;
            } else {
                right = mid;
            }
        }
        capture[left] = true;
    }

    vector<ll> areas(polygons_size);
    for (int i = 0; i < polygons_size; i++) {
        if (capture[i] || (i > 0 && capture[i - 1])) {
            areas[i] = double_area(polygons[i]);
        }
    }

    ll double_result = 0;
    for (int i = 0; i < polygons_size; i++) {
        if (capture[i]) {
            double_result += areas[i];
            if (i != polygons_size - 1) {
                double_result -= areas[i + 1];
            }
        }
    }

    cout << double_result / 2 << (double_result % 2 == 1 ? ".5" : "") << endl;
}
