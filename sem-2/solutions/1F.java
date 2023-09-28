import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Set;

public class CountLIS {
    public static final int MOD = 1_000_000_000 + 7;
    public static int[] tree;
    public static int[] count;
    public static int[] dpCount;
    public static int[] a;
    public static int[] t;
    public static int initialN;
    public static int n;

    public static void create(int v) {
        if (tree[2 * v + 1] > tree[2 * v + 2]) {
            tree[v] = tree[2 * v + 1];
            count[v] = count[2 * v + 1] % MOD;
        } else if (tree[2 * v + 2] > tree[2 * v + 1]) {
            tree[v] = tree[2 * v + 2];
            count[v] = count[2 * v + 2] % MOD;
        } else {
            tree[v] = tree[2 * v + 1];
            if (tree[v] != 0) {
                count[v] = (count[2 * v + 1] + count[2 * v + 2]) % MOD;
            } else {
                count[v] = count[2 * v + 1] % MOD;
            }
        }
    }

    public static void update(int v, int l, int r, int i, int value, int newCount, int type) {
        if (l + 1 == r) {
            if (type == 0 || value > tree[v]) {
                count[v] = newCount % MOD;
            } else {
                count[v] = (count[v] + newCount) % MOD;
            }
            tree[v] = value;
            return;
        }
        int m = l + (r - l) / 2;
        if (i < m) {
            update(2 * v + 1, l, m, i, value, newCount, type);
        } else {
            update(2 * v + 2, m, r, i, value, newCount, type);
        }
        create(v);
    }

    public static int[] get(int v, int l, int r, int ql, int qr) {
        if (qr <= l || ql >= r) {
            return new int[]{0, 1};
        }
        if (ql <= l && r <= qr) {
            return new int[]{tree[v], count[v] % MOD};
        }
        int m = (l + r) / 2;
        int[] maxLeftChild = get(2 * v + 1, l, m, ql, qr);
        int[] maxRightChild = get(2 * v + 2, m, r, ql, qr);
        if (maxLeftChild[0] > maxRightChild[0]) {
            return maxLeftChild;
        } else if (maxRightChild[0] > maxLeftChild[0]) {
            return maxRightChild;
        } else if (maxLeftChild[0] != 0) {
            return new int[]{maxLeftChild[0], (maxLeftChild[1] + maxRightChild[1]) % MOD};
        } else {
            return new int[]{maxLeftChild[0], Math.max(maxLeftChild[1], maxRightChild[1]) % MOD};
        }
    }

    public static void build(int v, int l, int r) {
        if (l + 1 == r) {
            tree[v] = 0;
            count[v] = 1;
            return;
        }
        int m = (l + r) / 2;
        build(2 * v + 1, l, m);
        build(2 * v + 2, m, r);
        create(v);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        initialN = Integer.parseInt(reader.readLine());
        a = new int[initialN];
        String[] line = reader.readLine().split(" ");
        for (int i = 0; i < initialN; i++) {
            a[i] = Integer.parseInt(line[i]);
        }
        n = (int) Math.pow(2, to2k(initialN));
        tree = new int[2 * n - 1];
        count = new int[2 * n - 1];
        dpCount = new int[initialN];
        t = new int[initialN];
        coordComp();
        for (int i = 0; i < initialN; i++) {
            t[a[i]] = 0;
        }
        build(0, 0, n);
        Set<Integer> set = new HashSet<>();
        for (int i = 0; i < initialN; i++) {
            int[] max_count = get(0, 0, n, 0, a[i]);
            int type = (set.contains(a[i])) ? 1 : 0;
            update(0, 0, n, a[i], max_count[0] + 1, max_count[1], type);
            if (type == 0 || (t[a[i]] < max_count[0] + 1)) {
                dpCount[a[i]] = max_count[1] % MOD;
            } else {
                dpCount[a[i]] = (dpCount[a[i]] + max_count[1]) % MOD;
            }
            t[a[i]] = max_count[0] + 1;
            set.add(a[i]);
        }
        set.clear();
        int maxValue = 0;
        int count = 0;
        for (int i = 0; i < initialN; i++) {
            maxValue = Math.max(maxValue, t[a[i]]);
        }
        for (int i = 0; i < initialN; i++) {
            if (t[a[i]] == maxValue && !set.contains(a[i])) {
                count = (count + dpCount[a[i]]) % MOD;
                set.add(a[i]);
            }
        }
        System.out.println(count);
    }

    public static void coordComp() {
        int[] b = new int[initialN];
        System.arraycopy(a, 0, b, 0, initialN);
        Arrays.sort(b);
        HashMap<Integer, Integer> map = new HashMap<>();
        for (int i = 0; i < initialN; i++) {
            map.put(b[i], i);
        }
        for (int i = 0; i < initialN; i++) {
            a[i] = map.get(a[i]);
        }
    }
    public static int to2k(int x) {
        int a = 1;
        int pow = 0;
        while (true) {
            if (a >= x) {
                return pow;
            }
            a *= 2;
            pow++;
        }
    }
}
