import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

public class RightNearestHigherNumber {
    public static List<Integer> vertex = new ArrayList<>();
    public static int[] tree;
    public static int[] index;
    public static String[] a;
    public static int n;
    public static int q;

    public static void update(int v, int l, int r, int i, int value) {
        if (l + 1 == r) {
            tree[v] = value;
            return;
        }
        int m = l + (r - l) / 2;
        if (i < m) {
            update(2 * v + 1, l, m, i, value);
        } else {
            update(2 * v + 2, m, r, i, value);
        }
        if (tree[2 * v + 1] >= tree[2 * v + 2]) {
            tree[v] = tree[2 * v + 1];
            index[v] = index[2 * v + 1];
        } else {
            tree[v] = tree[2 * v + 2];
            index[v] = index[2 * v + 2];
        }
    }

    public static void get(int v, int l, int r, int ql, int qr, int x) {
        if (qr <= l || r <= ql) {
            return;
        }
        if (ql <= l && r <= qr) {
            if (tree[v] >= x) {
                vertex.add(v);
                vertex.add(l);
                vertex.add(r);
            }
            return;
        }
        int m = l + (r - l) / 2;
        get(2 * v + 1, l, m, ql, qr, x);
        get(2 * v + 2, m, r, ql, qr, x);
    }

    public static int get(int v, int l, int r, int x) {
        if (l + 1 == r) {
            return index[v];
        }
        if (tree[2 * v + 1] >= x) {
            return get(2 * v + 1, l, l + (r - l) / 2, x);
        }
        return get(2 * v + 2, l + (r - l) / 2, r, x);
    }

    public static void build(int v, int l, int r) {
        if (l + 1 == r) {
            tree[v] = (l < a.length ? Integer.parseInt(a[l]) : Integer.MIN_VALUE);
            index[v] = (l < a.length ? l : Integer.MAX_VALUE);
            return;
        }
        int m = l + (r - l) / 2;
        build(2 * v + 1, l, m);
        build(2 * v + 2, m, r);
        if (tree[2 * v + 1] >= tree[2 * v + 2]) {
            tree[v] = tree[2 * v + 1];
            index[v] = index[2 * v + 1];
        } else {
            tree[v] = tree[2 * v + 2];
            index[v] = index[2 * v + 2];
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String[] line = reader.readLine().split(" ");
        n = Integer.parseInt(line[0]);
        int m = Integer.parseInt(line[1]);
        a = reader.readLine().split(" ");
        if (!is2k(n)) {
            n = (int) Math.pow(2, q);
        }
        tree = new int[2 * n - 1];
        index = new int[2 * n - 1];
        build(0, 0, n);
        for (int i = 0; i < m; i++) {
            line = reader.readLine().split(" ");
            if (Integer.parseInt(line[0]) == 0) {
                update(0, 0, n, Integer.parseInt(line[1]) - 1, Integer.parseInt(line[2]));
            } else {
                get(0, 0, n, Integer.parseInt(line[1]) - 1, n, Integer.parseInt(line[2]));
                if (vertex.isEmpty()) {
                    System.out.println(-1);
                } else {
                    System.out.println(get(vertex.get(0), vertex.get(1), vertex.get(2), Integer.parseInt(line[2])) + 1);
                    vertex.clear();
                }
            }
        }
    }

    public static boolean is2k(int x) {
        int a = 1;
        q = 0;
        while (true) {
            if (a == x) {
                return true;
            }
            if (a > x) {
                return false;
            }
            a *= 2;
            q++;
        }
    }
}
