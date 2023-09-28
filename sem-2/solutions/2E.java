import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

public class Stars {

    public static class Coord {
        int x;
        int y;

        public Coord(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }

    public static List<Coord> ls = new ArrayList<>();
    public static int[] tree;

    public static void add(int v, int l, int r, int i) {
        if (l + 1 == r) {
            tree[v]++;
            return;
        }
        int m = (l + r) / 2;
        if (i < m) {
            add(2 * v + 1, l, m, i);
        } else {
            add(2 * v + 2, m, r, i);
        }
        tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
    }

    public static int get(int v, int l, int r, int ql, int qr) {
        if (qr <= l || r <= ql) {
            return 0;
        }
        if (ql <= l && r <= qr) {
            return tree[v];
        }
        int m = (l + r) / 2;
        int sumLeft = get(2 * v + 1, l, m, ql, qr);
        int sumRight = get(2 * v + 2, m, r, ql, qr);
        return sumLeft + sumRight;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(reader.readLine());
        int maxY = 0;
        String[] line;
        for (int i = 0; i < n; i++) {
            line = reader.readLine().split(" ");
            maxY = Math.max(Integer.parseInt(line[1]), maxY);
            ls.add(new Coord(Integer.parseInt(line[0]), Integer.parseInt(line[1])));
        }
        ls.sort((o1, o2) -> {
            if (o1.x > o2.x) {
                return 1;
            } else {
                if (o1.x == o2.x) {
                    if (o1.y > o2.y) {
                        return 1;
                    } else {
                        if (o1.y < o2.y) {
                            return -1;
                        }
                        return 0;
                    }
                } else {
                    return -1;
                }
            }
        });
        maxY = (int) Math.pow(2, to2k(maxY));
        tree = new int[2 * maxY - 1];
        int[] levels = new int[n];
        for (Coord c : ls) {
            int level = get(0, 0, maxY, 0, c.y + 1);
            levels[level]++;
            add(0, 0, maxY, c.y);
        }
        for (int i = 0; i < n; i++) {
            System.out.println(levels[i]);
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
