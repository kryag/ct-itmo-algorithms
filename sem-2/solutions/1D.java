import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class KZero {
    public static int[] tree;
    public static String[] a;
    public static int countZero = 0;
    public static int n;
    public static int pow;
    public static int k;
    public static boolean flag = true;
    public static StringBuilder sb = new StringBuilder();

    public static void update(int v, int l, int r, int i, int value) {
        if (l + 1 == r) {
            tree[v] = (value == 0) ? 1 : 0;
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

    public static void get(int v, int l, int r, int ql, int qr) {
        if (!flag) {
            return;
        }
        if (qr <= l || r <= ql) {
            return;
        }
        if (ql <= l && r <= qr) {
            if (countZero + tree[v] >= k) {
                k -= countZero;
                flag = false;
                getAnswer(v, l, r);
            } else {
                countZero += tree[v];
            }
            return;
        }
        int m = l + (r - l) / 2;
        get(2 * v + 1, l, m, ql, qr);
        get(2 * v + 2, m, r, ql, qr);
    }

    public static void getAnswer(int v, int l, int r) {
        if (l + 1 == r) {
            k--;
            sb.append(l + 1).append(" ");
            return;
        }
        int m = l + (r - l) / 2;
        if (tree[2 * v + 1] >= k) {
            getAnswer(2 * v + 1, l, m);
        } else {
            k -= tree[2 * v + 1];
            getAnswer(2 * v + 2, m, r);
        }
    }

    public static void build(int v, int l, int r) {
        if (l + 1 == r) {
            if (l < a.length) {
                tree[v] = (Integer.parseInt(a[l]) == 0) ? 1 : 0;
            } else {
                tree[v] = 0;
            }
            return;
        }
        int m = l + (r - l) / 2;
        build(2 * v + 1, l, m);
        build(2 * v + 2, m, r);
        tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        n = Integer.parseInt(reader.readLine());
        a = reader.readLine().split(" ");
        if (!is2k(n)) {
            n = (int) Math.pow(2, pow);
        }
        tree = new int[2 * n - 1];
        build(0, 0, n);
        int countRequests = Integer.parseInt(reader.readLine());
        for (int i = 0; i < countRequests; i++) {
            String[] line = reader.readLine().split(" ");
            if (line[0].equals("u")) {
                update(0, 0, n, Integer.parseInt(line[1]) - 1, Integer.parseInt(line[2]));
            } else {
                k = Integer.parseInt(line[3]);
                get(0, 0, n, Integer.parseInt(line[1]) - 1, Integer.parseInt(line[2]));
                countZero = 0;
                flag = true;
                if (k != 0) {
                    sb.append(-1).append(" ");
                }
            }
        }
        sb.setLength(sb.length() - 1);
        System.out.println(sb);
    }

    public static boolean is2k(int x) {
        int a = 1;
        pow = 0;
        while (true) {
            if (a == x) {
                return true;
            }
            if (a > x) {
                return false;
            }
            a *= 2;
            pow++;
        }
    }
}
