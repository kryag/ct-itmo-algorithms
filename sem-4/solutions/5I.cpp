//
// Created by Aleksandr Kiriak on 20.05.2024.
//
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Point {
    int x, y;

    bool operator<(const Point& other) const {
        return y == other.y ? x < other.x : y < other.y;
    }
};

struct Vector {
    int x, y;

    Vector(const Point& A, const Point& B) {
        this->x = B.x - A.x;
        this->y = B.y - A.y;
    }
};

int skew_product(const Vector& A, const Vector& B) {
    return A.x * B.y - A.y * B.x;
}

int dist_sqr(const Point& A, const Point& B) {
    int dx = A.x - B.x;
    int dy = A.y - B.y;
    return dx * dx + dy * dy;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    vector<Point> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
    }

    int cur_time = 0;
    vector<int> time(n);
    while (true) {
        int start = -1;
        for (int i = 0; i < n; i++) {
            if (time[i] == 0 && (start == -1 || points[i] < points[start])) {
                start = i;
            }
        }
        if (start == -1) {
            break;
        }
        int cur = start;
        time[start] = -1;
        while (true) {
            int next = start;
            for (int i = 0; i < n; i++) {
                if (time[i] != 0) {
                    continue;
                }
                Vector cur_next(points[cur], points[next]);
                Vector cur_i(points[cur], points[i]);
                int skew = skew_product(cur_next, cur_i);
                if (skew > 0) {
                    continue;
                }
                if (skew < 0 || next == start || dist_sqr(points[cur], points[next]) > dist_sqr(points[cur], points[i])) {
                    next = i;
                    continue;
                }
            }
            if (next == start) {
                break;
            }
            time[next] = -1;
            cur = next;
        }

        cur_time++;
        for (int i = 0; i < n; i++) {
            if (time[i] == -1) {
                time[i] = cur_time;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << time[i] << endl;
    }
}
