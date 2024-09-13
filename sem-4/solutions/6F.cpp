//
// Created by Aleksandr Kiriak on 20.05.2024.
//
#include <iostream>
#include <vector>

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
    if (x == 0) {
        return 0;
    }
    return x > 0 ? 1 : -1;
}

ll skew_product(const Vector& A, const Vector& B) {
    return A.x * B.y - A.y * B.x;
}

// Находится ли точка P внутри (нестрого) многоугольника (не обязательно выпуклого) polygon.
bool is_point_in_polygon(const vector<Point>& polygon, const Point& P) {
    int n = (int) polygon.size();
    int count_intersections = 0;
    for (int i = 0; i < n; i++) {
        Point cur = polygon[i];
        Point next = polygon[(i + 1) % n];
        if (cur.y >= next.y) {
            swap(cur, next);
        }
        if (next.y < P.y || cur.y > P.y) {
            continue;
        }
        ll skew = sign(skew_product({cur, next}, {cur, P}));
        if (skew == 0) {
            return true;
        }
        if (skew > 0) {
            count_intersections++;
        }
    }
    return count_intersections % 2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    Point P{};
    cin >> P.x >> P.y;

    vector<Point> polygon(n);
    for (int i = 0; i < n; i++) {
        cin >> polygon[i].x >> polygon[i].y;
    }

    cout << (is_point_in_polygon(polygon, P) ? "YES" : "NO") << endl;
}
