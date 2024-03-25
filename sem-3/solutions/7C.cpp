#include <iostream>
#include <vector>

using namespace std;

template <typename T>
void print_vector(vector<T> const& v) {
    for (auto const& x: v) {
        cout << x << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);
    vector<long long> pref(n + 2);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pref[i + 1] = pref[i] + a[i];
    }

    vector<int> mark_order(n);
    for (int i = 0; i < n; i++) {
        cin >> mark_order[i];
    }

    vector<int> left_mark(n + 2), right_mark(n + 2);
    vector<long long> answer(n);
    long long max_sum = 0LL;
    for (int i = n - 1; i >= 0; i--) {
        answer[i] = max_sum;

        int mark = mark_order[i];
        int left = left_mark[mark - 1] == 0 ? mark : left_mark[mark - 1];
        int right = right_mark[mark + 1] == 0 ? mark : right_mark[mark + 1];

        if (pref[right] - pref[left - 1] > max_sum) {
            max_sum = pref[right] - pref[left - 1];
        }

        left_mark[right] = left;
        right_mark[left] = right;
    }

    print_vector(answer);
}
