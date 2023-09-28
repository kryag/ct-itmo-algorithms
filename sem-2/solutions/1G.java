import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.HashMap;

public class EnemyWeak {
    public static int[] tree;
    public static int[] a;
    public static int[] countLeft;
    public static int[] countRight;
    public static int n;
    public static int initialN;

    public static void update(int v, int l, int r, int i, int value) {
        if (l + 1 == r) {
            tree[v] += value;
            return;
        }
        int m = l + (r - l) / 2;
        if (i < m) {
            update(2 * v + 1, l, m, i, value);
        } else {
            update(2 * v + 2, m, r, i, value);
        }
        tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
    }

    public static int get(int v, int l, int r, int ql, int qr) {
        if (qr <= l || ql >= r) {
            return 0;
        }
        if (ql <= l && r <= qr) {
            return tree[v];
        }
        int m = l + (r - l) / 2;
        int sum1 = get(2 * v + 1, l, m, ql, qr);
        int sum2 = get(2 * v + 2, m, r, ql, qr);
        return sum1 + sum2;
    }

    public static void build(int v, int l, int r) {
        if (l + 1 == r) {
            tree[v] = 0;
            return;
        }
        int m = l + (r - l) / 2;
        build(2 * v + 1, l, m);
        build(2 * v + 2, m, r);
        tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        initialN = Integer.parseInt(reader.readLine());
        a = new int[initialN];
        countLeft = new int[initialN];
        countRight = new int[initialN];
        String[] line = reader.readLine().split(" ");
        for (int i = 0; i < initialN; i++) {
            a[i] = Integer.parseInt(line[i]);
        }
        n = (int) Math.pow(2, to2k(initialN));
        tree = new int[2 * n - 1];
        coordComp();
        build(0, 0, n);
        update(0, 0, n, a[0], 1);
        for (int i = 1; i < initialN - 1; i++) {
            countLeft[i] = get(0, 0, n, a[i] + 1, initialN);
            update(0, 0, n, a[i], 1);
        }

        build(0, 0, n);
        update(0, 0, n, a[initialN - 1], 1);
        for (int i = initialN - 2; i > 0; i--) {
            countRight[i] = get(0, 0, n, 0, a[i]);
            update(0, 0, n, a[i], 1);
        }

        long count = 0L;
        for (int i = 1; i < initialN - 1; i++) {
            count += (long) countLeft[i] * countRight[i];
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
