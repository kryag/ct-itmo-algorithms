import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PetyaAndArray {
    public static long[][] tree;
    public static long[] prefSum;
    public static long t;
    public static int n;

    public static int get(int v, int l, int r, int ql, int qr, long x) {
        if (qr <= l || r <= ql) {
            return 0;
        }
        if (ql <= l && r <= qr) {
            return binarySearch(tree[v], x);
        }
        int m = (l + r) / 2;
        int countLeft = get(2 * v + 1, l, m, ql, qr, x);
        int countRight = get(2 * v + 2, m, r, ql, qr, x);
        return countLeft + countRight;
    }

    public static int binarySearch(long[] a, long x) {
        int l = -1;
        int r = a.length;
        while (l + 1 < r) {
            int m = (l + r) / 2;
            if (a[m] <= x) {
                l = m;
            } else {
                r = m;
            }
        }
        return a.length - l - 1;
    }

    public static long[] merge(long[] first, long[] second) {
        int f = 0;
        int s = 0;
        int r = 0;
        long[] result = new long[first.length + second.length];
        while (r != result.length) {
            if ((f < first.length && s < second.length && first[f] <= second[s]) ||
                    (!(f < first.length && s < second.length) && s == second.length)) {
                result[r] = first[f];
                f++;
            } else {
                result[r] = second[s];
                s++;
            }
            r++;
        }
        return result;
    }

    public static void build(int v, int l, int r) {
        if (l + 1 == r) {
            tree[v] = (l < n + 1) ? new long[]{prefSum[l]} : new long[]{Long.MIN_VALUE};
            return;
        }
        int m = (l + r) / 2;
        build(2 * v + 1, l, m);
        build(2 * v + 2, m, r);
        long[] merge = merge(tree[2 * v + 1], tree[2 * v + 2]);
        tree[v] = merge;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String[] line = reader.readLine().split(" ");
        n = Integer.parseInt(line[0]);
        t = Long.parseLong(line[1]);
        line = reader.readLine().split(" ");
        prefSum = new long[n + 1];
        prefSum[0] = 0L;
        long sum = 0L;
        for (int i = 0; i < n; i++) {
            sum += Integer.parseInt(line[i]);
            prefSum[i + 1] = sum;
        }
        int treeLen = (int) Math.pow(2, to2k(n + 1));
        tree = new long[2 * treeLen - 1][];
        build(0, 0, treeLen);
        long answer = 0L;
        for (int i = 0; i < n + 1; i++) {
            long diff = prefSum[i] - t;
            answer += get(0, 0, treeLen, 0, i, diff);
        }
        System.out.println(answer);
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
