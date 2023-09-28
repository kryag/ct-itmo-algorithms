import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class XORSegment {
    public static int[][] treeSum;
    public static int[][] treeFlag;
    public static int[] a;
    public static int n;

    public static void propagate(int bit, int v, int l, int r) {
        if (treeFlag[bit][v] != -1) {
            for (int i = 2 * v + 1; i <= 2 * v + 2; i++) {
                treeSum[bit][i] = ((r - l) / 2) - treeSum[bit][i];
                treeFlag[bit][i] = (treeFlag[bit][i] == 1) ? -1 : 1;
            }
            treeFlag[bit][v] = -1;
        }
    }

    public static void xor(int v, int l, int r, int ql, int qr, int bit) {
        if (qr <= l || r <= ql) {
            return;
        }
        if (ql <= l && r <= qr) {
            treeSum[bit][v] = (r - l) - treeSum[bit][v];
            treeFlag[bit][v] = (treeFlag[bit][v] == 1) ? -1 : 1;
            return;
        }
        propagate(bit, v, l, r);
        int m = (l + r) / 2;
        xor(2 * v + 1, l, m, ql, qr, bit);
        xor(2 * v + 2, m, r, ql, qr, bit);
        treeSum[bit][v] = treeSum[bit][2 * v + 1] + treeSum[bit][2 * v + 2];
    }

    public static long get(int v, int l, int r, int ql, int qr, int bit) {
        if (qr <= l || r <= ql) {
            return 0;
        }
        if (ql <= l && r <= qr) {
            return (long) Math.pow(2, bit) * (long) treeSum[bit][v];
        }
        propagate(bit, v, l, r);
        int m = (l + r) / 2;
        long sumLeft = get(2 * v + 1, l, m, ql, qr, bit);
        long sumRight = get(2 * v + 2, m, r, ql, qr, bit);
        return sumLeft + sumRight;
    }

    public static void build(int v, int l, int r, int bit) {
        if (l + 1 == r) {
            treeSum[bit][v] = (l < n) ? ((a[l] >>> bit) % 2) : 0;
            treeFlag[bit][v] = -1;
            return;
        }
        int m = (l + r) / 2;
        build(2 * v + 1, l, m, bit);
        build(2 * v + 2, m, r, bit);
        treeSum[bit][v] = treeSum[bit][2 * v + 1] + treeSum[bit][2 * v + 2];
        treeFlag[bit][v] = -1;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        n = Integer.parseInt(reader.readLine());
        String[] line = reader.readLine().split(" ");
        a = new int[n];
        for (int i = 0; i < n; i++) {
            a[i] = Integer.parseInt(line[i]);
        }
        int treeLen = (int) Math.pow(2, to2k(n));
        treeSum = new int[20][2 * treeLen - 1];
        treeFlag = new int[20][2 * treeLen - 1];
        for (int i = 0; i < 20; i++) {
            build(0, 0, treeLen, i);
        }
        int m = Integer.parseInt(reader.readLine());
        for (int i = 0; i < m; i++) {
            line = reader.readLine().split(" ");
            if (line[0].equals("1")) {
                long answer = 0;
                for (int j = 0; j < 20; j++) {
                    answer += get(0, 0, treeLen, Integer.parseInt(line[1]) - 1, Integer.parseInt(line[2]), j);
                }
                System.out.println(answer);
            } else {
                String x = Integer.toString(Integer.parseInt(line[3]), 2);
                x = "0".repeat(20 - x.length()) + x;
                for (int j = 0; j < 20; j++) {
                    if (x.charAt(x.length() - j - 1) == '1') {
                        xor(0, 0, treeLen, Integer.parseInt(line[1]) - 1, Integer.parseInt(line[2]), j);
                    }
                }
            }
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
