import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

public class Windows {
    public static List<Coord> ls = new ArrayList<>();
    public static int[] treeMax;
    public static int[] treeIndex;
    public static int[] treeAdd;
    public static int[] flag;

    public static void propagate(int v) {
        if (flag[v] != -1) {
            for (int i = 2 * v + 1; i <= 2 * v + 2; i++) {
                treeMax[i] += treeAdd[v];
                treeAdd[i] += treeAdd[v];
                flag[i] = 1;
            }
            treeAdd[v] = 0;
            flag[v] = -1;
        }
    }

    public static void add(int v, int l, int r, int ql, int qr, int value) {
        if (r <= ql || qr <= l) {
            return;
        }
        if (ql <= l && r <= qr) {
            treeAdd[v] += value;
            treeMax[v] += value;
            flag[v] = 1;
            return;
        }
        propagate(v);
        int m = (l + r) / 2;
        add(2 * v + 1, l, m, ql, qr, value);
        add(2 * v + 2, m, r, ql, qr, value);
        if (treeMax[2 * v + 1] >= treeMax[2 * v + 2]) {
            treeMax[v] = treeMax[2 * v + 1];
            treeIndex[v] = treeIndex[2 * v + 1];
        } else {
            treeMax[v] = treeMax[2 * v + 2];
            treeIndex[v] = treeIndex[2 * v + 2];
        }
        flag[v] = -1;
        treeAdd[v] = 0;
    }

    public static int[] get() {
        return new int[]{treeMax[0], treeIndex[0]};
    }

    public static void build(int v, int l, int r) {
        if (l + 1 == r) {
            treeIndex[v] = l;
            return;
        }
        int m = (l + r) / 2;
        build(2 * v + 1, l, m);
        build(2 * v + 2, m, r);
        treeIndex[v] = treeIndex[2 * v + 1];
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(reader.readLine());
        int maxY = Integer.MIN_VALUE;
        int minY = Integer.MAX_VALUE;
        String[] line;
        for (int i = 0; i < n; i++) {
            line = reader.readLine().split(" ");
            int x1 = Integer.parseInt(line[0]);
            int y1 = Integer.parseInt(line[1]);
            int x2 = Integer.parseInt(line[2]);
            int y2 = Integer.parseInt(line[3]);
            maxY = Math.max(maxY, y2);
            minY = Math.min(minY, y1);
            ls.add(new Coord(x1, y1, x2, y2, -1));
            ls.add(new Coord(x2, y2, x1, y1, 1));
        }
        ls.sort((o1, o2) -> {
            if (o1.x1 != o2.x1) {
                return Integer.compare(o1.x1, o2.x1);
            } else {
                return Integer.compare(o1.type, o2.type);
            }
        });
        int shift = (minY < 0) ? -minY : 0;
        n = (int) Math.pow(2 , to2k(maxY + 1 + shift));
        treeMax = new int[2 * n - 1];
        treeAdd = new int[2 * n - 1];
        treeIndex = new int[2 * n - 1];
        flag = new int[2 * n - 1];
        for (int i = 0; i < 2 * n - 1; i++) {
            treeMax[i] = 0;
            treeAdd[i] = 0;
            flag[i] = -1;
        }
        build(0, 0, n);
        int x = 0;
        int y = 0;
        int count = 0;
        for (Coord c : ls) {
            if (c.type == -1) {
                add(0, 0, n, c.y1 + shift, c.y2 + shift + 1, 1);
            } else {
                int[] ans = get();
                if (ans[0] > count) {
                    count = ans[0];
                    y = ans[1];
                    x = c.x1;
                }
                add(0, 0, n, c.y2 + shift, c.y1 + shift + 1, -1);
            }
        }
        y -= shift;
        System.out.println(count);
        System.out.println(x + " " + y);
    }

    public static class Coord {
        int x1, y1, x2, y2, type;

        public Coord(int x1, int y1, int x2, int y2, int type) {
            this.x1 = x1;
            this.y1 = y1;
            this.x2 = x2;
            this.y2 = y2;
            this.type = type;
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
