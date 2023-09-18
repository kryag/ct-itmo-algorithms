import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Company {
    public static int[] p;
    public static int[] r;

    public static int find(int x) {
        if (p[x] != x) {
            p[x] = find(p[x]);
        }
        return p[x];
    }

    public static void team(int x, int y) {
        x = find(x);
        y = find(y);
        p[x] = y;
    }

    public static boolean ask(int x, int y) {
        return find(x) == find(y);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String[] line = reader.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        int q = Integer.parseInt(line[1]);
        p = new int[n];
        r = new int[n];
        for (int i = 0; i < n; i++) {
            p[i] = i;
            r[i] = i + 1;
        }
        r[n - 1] = Integer.MAX_VALUE;
        for (int i = 0; i < q; i++) {
            line = reader.readLine().split(" ");
            int type = Integer.parseInt(line[0]);
            if (type == 1) {
                team(Integer.parseInt(line[1]) - 1, Integer.parseInt(line[2]) - 1);
            } else {
                if (type == 2) {
                    int prev = Integer.parseInt(line[1]) - 1;
                    int cur = prev + 1;
                    while (cur <= Integer.parseInt(line[2]) - 1) {
                        int parentPrev = p[prev];
                        int parentCur = p[cur];
                        if (parentPrev == parentCur) {
                            int tempCur = cur;
                            cur = r[cur];
                            r[tempCur] = r[Integer.parseInt(line[2]) - 1];
                            continue;
                        }
                        int tempCur = cur;
                        team(parentPrev, parentCur);
                        prev = cur;
                        cur = r[cur];
                        r[tempCur] = r[Integer.parseInt(line[2]) - 1];
                    }
                } else {
                    if (ask(Integer.parseInt(line[1]) - 1, Integer.parseInt(line[2]) - 1)) {
                        System.out.println("YES");
                    } else {
                        System.out.println("NO");
                    }
                }
            }
        }
    }
}
