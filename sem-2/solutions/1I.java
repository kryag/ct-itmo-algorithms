import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Mario {
    public static long[] treeMax;
    public static long[] treeMin;
    public static String[] a;
    public static int n;
    public static int pow;

    public static void update(int v, int l, int r, int i, int value, int type) {
        if (l + 1 == r) {
            if (type == 0) {
                treeMax[v] += value;
                treeMin[v] += value;
            } else {
                treeMax[v] -= value;
                treeMin[v] -= value;
            }
            return;
        }
        int m = l + (r - l) / 2;
        if (i < m) {
            update(2 * v + 1, l, m, i, value, type);
        } else {
            update(2 * v + 2, m, r, i, value, type);
        }
        treeMax[v] = Math.max(treeMax[2 * v + 1], treeMax[2 * v + 2]);
        treeMin[v] = Math.min(treeMin[2 * v + 1], treeMin[2 * v + 2]);
    }

    public static long getMax(int v, int l, int r, int ql, int qr) {
        if (qr <= l || ql >= r) {
            return Integer.MIN_VALUE;
        }
        if (ql <= l && r <= qr) {
            return treeMax[v];
        }
        int m = l + (r - l) / 2;
        long maxLeftChild = getMax(2 * v + 1, l, m, ql, qr);
        long maxRightChild = getMax(2 * v + 2, m, r, ql, qr);
        return Math.max(maxLeftChild, maxRightChild);
    }

    public static long getMin(int v, int l, int r, int ql, int qr) {
        if (qr <= l || ql >= r) {
            return Integer.MAX_VALUE;
        }
        if (ql <= l && r <= qr) {
            return treeMin[v];
        }
        int m = l + (r - l) / 2;
        long minLeftChild = getMin(2 * v + 1, l, m, ql, qr);
        long minRightChild = getMin(2 * v + 2, m, r, ql, qr);
        return Math.min(minLeftChild, minRightChild);
    }

    public static void build(int v, int l, int r) {
        if (l + 1 == r) {
            if (l < a.length - 1) {
                treeMax[v] = Integer.parseInt(a[l + 1]) - Integer.parseInt(a[l]);
                treeMin[v] = Integer.parseInt(a[l + 1]) - Integer.parseInt(a[l]);
            } else {
                treeMax[v] = Integer.MIN_VALUE;
                treeMin[v] = Integer.MAX_VALUE;
            }
            return;
        }
        int m = l + (r - l) / 2;
        build(2 * v + 1, l, m);
        build(2 * v + 2, m, r);
        treeMax[v] = Math.max(treeMax[2 * v + 1], treeMax[2 * v + 2]);
        treeMin[v] = Math.min(treeMin[2 * v + 1], treeMin[2 * v + 2]);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String[] line = reader.readLine().split(" ");
        n = Integer.parseInt(line[0]);
        int m = Integer.parseInt(line[1]);
        a = reader.readLine().split(" ");
        if (!is2k(n)) {
            n = (int) Math.pow(2, pow);
        }
        treeMax = new long[2 * n - 1];
        treeMin = new long[2 * n - 1];
        build(0, 0, n);
        for (int i = 0; i < m; i++) {
            line = reader.readLine().split(" ");
            if (Integer.parseInt(line[0]) == 2) {
                if (Integer.parseInt(line[1]) > 1) {
                    update(0, 0, n, Integer.parseInt(line[1]) - 2, Integer.parseInt(line[3]), 0);
                }
                if (Integer.parseInt(line[2]) < a.length) {
                    update(0, 0, n, Integer.parseInt(line[2]) - 1, Integer.parseInt(line[3]), 1);
                }
            } else {
                int ql = Integer.parseInt(line[1]) - 1;
                int qr = Integer.parseInt(line[2]) - 1;
                long result;
                if (ql < qr) {
                    result = getMax(0, 0, n, ql, qr);
                } else {
                    result = getMin(0, 0, n, qr, ql);
                }
                if ((result > 1 && ql < qr) || (result < -1 && ql > qr)) {
                    System.out.println("NO");
                } else {
                    System.out.println("YES");
                }
            }
        }
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
