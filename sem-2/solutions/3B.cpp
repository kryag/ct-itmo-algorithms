#include <iostream>

int fenwick[129][129][129] = {0};
int n;

int dec(int x) {
    x -= x & (-x);
    return x;
}

int query(int xq, int yq, int zq) {
    int x, y, z;
    int answer = 0;
    x = xq;
    while (x > 0) {
        y = yq;
        while (y > 0) {
            z = zq;
            while (z > 0) {
                answer += fenwick[x][y][z];
                z = dec(z);
            }
            y = dec(y);
        }
        x = dec(x);
    }
    return answer;
}

int inc(int x) {
    x += x & (-x);
    return x;
}

void update(int xq, int yq, int zq, int value) {
    int x, y, z;
    x = xq + 1;
    while (x < n + 1) {
        y = yq + 1;
        while (y < n + 1) {
            z = zq + 1;
            while (z < n + 1) {
                fenwick[x][y][z] += value;
                z = inc(z);
            }
            y = inc(y);
        }
        x = inc(x);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int c[7], ans[8], m = 0, result;
    std::cin >> n;
    while (true) {
        std::cin >> m;
        if (m == 1) {
            std::cin >> c[0] >> c[2] >> c[4] >> c[6];
            update(c[0], c[2], c[4], c[6]);
        } else if (m == 2) {
            std::cin >> c[0] >> c[2] >> c[4] >> c[1] >> c[3] >> c[5];
            ans[0] = query(c[1] + 1, c[3] + 1, c[5] + 1);
            ans[1] = query(c[0], c[2], c[4]);
            ans[2] = query(c[0], c[2], c[5] + 1);
            ans[3] = query(c[1] + 1, c[3] + 1, c[4]);
            ans[4] = query(c[0], c[3] + 1, c[4]);
            ans[5] = query(c[1] + 1, c[2], c[5] + 1);
            ans[6] = query(c[1] + 1, c[2], c[4]);
            ans[7] = query(c[0], c[3] + 1, c[5] + 1);
            result = 0;
            for (int i = 0; i < 8; ++i) {
                result += (i % 2 == 0) ? ans[i] : -ans[i];
            }
            std::cout << result << '\n';
        } else {
            return 0;
        }
    }
}
