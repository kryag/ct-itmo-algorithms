#include <iostream>
#include <vector>
using namespace std;

vector<long long> a(300000);
long long value = 0;
int head = 0;
int tail = 0;
int mod = 300000;

void add(long long x) {
    a[tail % mod] = x - value;
    tail = (tail + 1) % mod;
}

void blame(long long x, long long y) {
    a[head % mod] = a[head % mod] + x - y;
    value += y;
}

long long out() {
    long long result = a[head % mod] + value;
    head = (head + 1) % mod;
    return result;
}

int main() {
    int n;
    cin >> n;
    int f;
    long long s;
    long long t;
    for (int i = 0; i < n; i++) {
        cin >> f;
        if (f == 1) {
            cin >> s;
            add(s);
        }
        if (f == 2) {
            cin >> s;
            cin >> t;
            blame(s, t);
        }
        if (f == 3) {
            long long ans = out();
            cout << ans << '\n';
        }
    }
    return 0;
}
