import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class RMQ {
    public static int[] tree;
    public static int[] index;
    public static String[] a;
    public static int n;
    public static int q;

    public static int[] get(int v, int l, int r, int ql, int qr) {
        if (qr <= l || ql >= r) {
            return new int[]{Integer.MIN_VALUE, -1};
        }
        if (ql <= l && r <= qr) {
            return new int[]{tree[v], index[v]};
        }
        int m = (l + r) / 2;
        int[] maxLeftChild = get(2 * v + 1, l, m, ql, qr);
        int[] maxRightChild = get(2 * v + 2, m, r, ql, qr);
        if (maxLeftChild[0] >= maxRightChild[0]) {
            return maxLeftChild;
        }
        return maxRightChild;
    }

    public static void build(int v, int l, int r) {
        if (l + 1 == r) {
            tree[v] = (l < a.length ? Integer.parseInt(a[l]) : Integer.MIN_VALUE);
            index[v] = l;
            return;
        }
        int m = (l + r) / 2;
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
        n = Integer.parseInt(reader.readLine());
        a = reader.readLine().split(" ");
        if (!is2k(n)) {
            n = (int) Math.pow(2, q);
        }
        tree = new int[2 * n - 1];
        index = new int[2 * n - 1];
        build(0, 0, n);
        int countQuery = Integer.parseInt(reader.readLine());
        for (int i = 0; i < countQuery; i++) {
            String[] line = reader.readLine().split(" ");
            int[] ans = get(0, 0, n, Integer.parseInt(line[0]) - 1, Integer.parseInt(line[1]));
            System.out.println(ans[0] + " " + (ans[1] + 1));
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
