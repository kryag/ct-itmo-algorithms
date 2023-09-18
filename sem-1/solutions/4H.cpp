#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int main() {
    int n;
    cin >> n;
    int k;
    cin >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a[i] = x;
    }
    deque<int> value;
    deque<int> ind;
    int size = 0;
    for (int i = 0; i < k; i++) {
        while (size != 0 && a[i] < value.back()) {
            value.pop_back();
            ind.pop_back();
            size--;
        }
        value.push_back(a[i]);
        ind.push_back(i);
        size++;
    }
    cout << value.front() << '\n';
    for (int i = k; i < n; i++) {
        while (size != 0 && a[i] < value.back()) {
            value.pop_back();
            ind.pop_back();
            size--;
        }
        value.push_back(a[i]);
        ind.push_back(i);
        size++;
        if (ind.front() < i - k + 1) {
            value.pop_front();
            ind.pop_front();
            size--;
        }
        cout << value.front() << '\n';
    }
    return 0;
}
