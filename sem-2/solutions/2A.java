import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MassAddMax {
    public static int[] treeMax;
    public static int[] treeAdd;
    public static int[] a;
    public static int initN;

    public static void propagate(int v) {
        treeAdd[2 * v + 1] += treeAdd[v];
        treeMax[2 * v + 1] += treeAdd[v];
        treeAdd[2 * v + 2] += treeAdd[v];
        treeMax[2 * v + 2] += treeAdd[v];
        treeAdd[v] = 0;
    }

    public static void add(int v, int l, int r, int ql, int qr, int value) {
        if (l >= qr || ql >= r) {
            return;
        }
        if (ql <= l && r <= qr) {
            treeAdd[v] += value;
            treeMax[v] += value;
            return;
        }
        propagate(v);
        int m = (l + r) / 2;
        add(2 * v + 1, l, m, ql, qr, value);
        add(2 * v + 2, m, r, ql, qr, value);
        treeMax[v] = Math.max(treeMax[2 * v + 1], treeMax[2 * v + 2]);
    }

    public static int get(int v, int l, int r, int ql, int qr) {
        if (l >= qr || ql >= r) {
            return Integer.MIN_VALUE;
        }
        if (ql <= l && r <= qr) {
            return treeMax[v];
        }
        propagate(v);
        int m = (l + r) / 2;
        int maxLeft = get(2 * v + 1, l, m, ql, qr);
        int maxRight = get(2 * v + 2, m, r, ql, qr);
        return Math.max(maxLeft, maxRight);
    }

    public static void build(int v, int l, int r) {
        if (l + 1 == r) {
            treeMax[v] = (l < initN) ? a[l] : Integer.MIN_VALUE;
            treeAdd[v] = 0;
            return;
        }
        int m = (r + l) / 2;
        build(2 * v + 1, l, m);
        build(2 * v + 2, m, r);
        treeMax[v] = Math.max(treeMax[2 * v + 1], treeMax[2 * v + 2]);
        treeAdd[v] = treeAdd[2 * v + 1] + treeAdd[2 * v + 2];
    }


    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        initN = Integer.parseInt(reader.readLine());
        a = new int[initN];
        String[] line = reader.readLine().split(" ");
        for (int i = 0; i < initN; i++) {
            a[i] = Integer.parseInt(line[i]);
        }
        int n = (int) Math.pow(2, to2k(initN));
        treeMax = new int[2 * n - 1];
        treeAdd = new int[2 * n - 1];
        build(0, 0, n);
        int m = Integer.parseInt(reader.readLine());
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < m; i++) {
            line = reader.readLine().split(" ");
            if (line[0].equals("m")) {
                sb.append(get(0, 0, n, Integer.parseInt(line[1]) - 1, Integer.parseInt(line[2]))).append(" ");
            } else {
                add(0, 0, n, Integer.parseInt(line[1]) - 1, Integer.parseInt(line[2]), Integer.parseInt(line[3]));
            }
        }
        sb.setLength(sb.length() - 1);
        System.out.println(sb);
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
