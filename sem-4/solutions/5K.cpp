//
// Created by Aleksandr Kiriak on 20.05.2024.
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

ll skew_product(const Vector& A, const Vector& B) {
    return A.x * B.y - A.y * B.x;
}

ll dist_sqr(const Point& A, const Point& B) {
    ll dx = A.x - B.x;
    ll dy = A.y - B.y;
    return dx * dx + dy * dy;
}

bool is_point_on_line(const Point& A, const Point& B, const Point& P) {
    return ((P.x - A.x) * (B.y - A.y)) == ((P.y - A.y) * (B.x - A.x));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    vector<Point> v(n);
    Point start{};
    for (int i = 0; i < n; i++) {
        cin >> v[i].x >> v[i].y;
        if (i == 0 || v[i] < start) {
            start = v[i];
        }
    }

    sort(v.begin(), v.end(), [&](const auto& a, const auto& b) {
        ll skew = skew_product({start, a}, {start, b});
        if (skew == 0) {
            return dist_sqr(start, a) > dist_sqr(start, b);
        }
        return skew > 0;
    });

    vector<Point> points;
    points.push_back(start);
    for (auto const& p : v) {
        if (p != start && points.back() != p && (points.size() == 1 || !is_point_on_line(start, points.back(), p))) {
            points.push_back(p);
        }
    }

    vector<Point> path;
    for (auto point : points) {
        while (path.size() >= 2 && skew_product({path[path.size() - 2], path.back()}, {path.back(), point}) <= 0) {
            path.pop_back();
        }
        path.push_back(point);
    }

    int size = (int) path.size();
    ll s = 0;

    cout << size << endl;
    for (int i = 0; i < size; i++) {
        cout << path[i].x << ' ' << path[i].y << endl;
        int next = (i + 1) % size;
        s += (path[next].y + path[i].y) * (path[next].x - path[i].x);
    }
    s = abs(s);
    cout << s / 2 << (s % 2 ? ".5" : "") << endl;
}
