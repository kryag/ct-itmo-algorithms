import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

public class Zeroes {
    public static List<Integer> vertex = new ArrayList<>();
    public static int[] tree;
    public static int[] countZeroes;
    public static int[] maxPrefix;
    public static int[] maxSuffix;
    public static String[] a;
    public static int n;
    public static int q;

    public static void create(int v, int l, int r) {
        int count = (r - l) / 2;
        if (maxPrefix[2 * v + 1] == count) {
            maxPrefix[v] = count + maxPrefix[2 * v + 2];
        } else {
            maxPrefix[v] = maxPrefix[2 * v + 1];
        }
        if (maxSuffix[2 * v + 2] == count) {
            maxSuffix[v] = maxSuffix[2 * v + 1] + count;
        } else {
            maxSuffix[v] = maxSuffix[2 * v + 2];
        }
        int max1 = Math.max(countZeroes[2 * v + 1], countZeroes[2 * v + 2]);
        int max2 = maxSuffix[2 * v + 1] + maxPrefix[2 * v + 2];
        countZeroes[v] = Math.max(max1, max2);
        tree[v] = countZeroes[v];
    }

    public static void leaf(int v) {
        if (tree[v] == 0) {
            countZeroes[v] = 1;
            maxPrefix[v] = 1;
            maxSuffix[v] = 1;
        } else {
            countZeroes[v] = 0;
            maxPrefix[v] = 0;
            maxSuffix[v] = 0;
        }
    }

    public static void update(int v, int l, int r, int i, int value) {
        if (l + 1 == r) {
            tree[v] = value;
            leaf(v);
            return;
        }
        int m = l + (r - l) / 2;
        if (i < m) {
            update(2 * v + 1, l, m, i, value);
        } else {
            update(2 * v + 2, m, r, i, value);
        }
        create(v, l, r);
    }

    public static void get(int v, int l, int r, int ql, int qr) {
        if (qr <= l || r <= ql) {
            return;
        }
        if (ql <= l && r <= qr) {
            vertex.add(v);
            vertex.add(l);
            vertex.add(r);
            return;
        }
        int m = l + (r - l) / 2;
        get(2 * v + 1, l, m, ql, qr);
        get(2 * v + 2, m, r, ql, qr);
    }

    public static long getAnswer() {
        if (vertex.isEmpty()) {
            return 0;
        }
        long curSum = 0L;
        long maxSum = 0L;
        for (int i = 0; i < vertex.size(); i += 3) {
            int v = vertex.get(i);
            int count = vertex.get(i + 2) - vertex.get(i + 1);
            if (maxPrefix[v] == count) {
                curSum += count;
            } else {
                curSum += maxPrefix[v];
                maxSum = Math.max(maxSum, curSum);
                curSum = maxSuffix[v];
            }
        }
        maxSum = Math.max(maxSum, curSum);
        for (int i = 0; i < vertex.size(); i += 3) {
            int v = vertex.get(i);
            maxSum = Math.max(countZeroes[v], maxSum);
        }
        vertex.clear();
        return maxSum;
    }

    public static void build(int v, int l, int r) {
        if (l + 1 == r) {
            tree[v] = (l < a.length ? Integer.parseInt(a[l]) : Integer.MIN_VALUE);
            leaf(v);
            return;
        }
        int m = l + (r - l) / 2;
        build(2 * v + 1, l, m);
        build(2 * v + 2, m, r);
        create(v, l, r);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        n = Integer.parseInt(reader.readLine());
        a = reader.readLine().split(" ");
        int countQuery = Integer.parseInt(reader.readLine());
        if (!is2k(n)) {
            n = (int) Math.pow(2, q);
        }
        tree = new int[2 * n - 1];
        countZeroes = new int[2 * n - 1];
        maxPrefix = new int[2 * n - 1];
        maxSuffix = new int[2 * n - 1];
        build(0, 0, n);
        for (int i = 0; i < countQuery; i++) {
            String[] line = reader.readLine().split(" ");
            if (line[0].equals("UPDATE")) {
                update(0, 0, n, Integer.parseInt(line[1]) - 1, Integer.parseInt(line[2]));
            } else {
                get(0, 0, n, Integer.parseInt(line[1]) - 1, Integer.parseInt(line[2]));
                System.out.println(getAnswer());
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
