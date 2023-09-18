import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class CollectExp {
    public static List<Set<Integer>> ls = new ArrayList<>();
    public static int[] exp;
    public static int[] newExp;
    public static int[] p;
    public static int n;

    public static int find(int x) {
        if (p[x] != x) {
            p[x] = find(p[x]);
        }
        return p[x];
    }

    public static void join(int x, int y) {
        x = find(x);
        y = find(y);
        for (Integer i : ls.get(x)) {
            exp[i] += newExp[x] - newExp[y];
        }
        p[x] = y;
        ls.get(y).addAll(ls.get(x));
    }

    public static void add(int x, int v) {
        x = find(x);
        newExp[x] += v;
    }

    public static void get(int x) {
        System.out.println(exp[x] + newExp[find(x)]);
    }

    public static void joinLess(int x, int y) {
        x = find(x);
        y = find(y);
        if (ls.get(x).size() <= ls.get(y).size()) {
            join(x, y);
        } else {
            join(y, x);
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String[] line = reader.readLine().split(" ");
        n = Integer.parseInt(line[0]);
        int m = Integer.parseInt(line[1]);
        exp = new int[n];
        newExp = new int[n];
        p = new int[n];
        for (int i = 0; i < n; i++) {
            Set<Integer> temp = new HashSet<>();
            temp.add(i);
            ls.add(temp);
            p[i] = i;
        }
        for (int i = 0; i < m; i++) {
            line = reader.readLine().split(" ");
            if (line[0].equals("join")) {
                joinLess(Integer.parseInt(line[1]) - 1, Integer.parseInt(line[2]) - 1);
            } else if (line[0].equals("add")) {
                add(Integer.parseInt(line[1]) - 1, Integer.parseInt(line[2]));
            } else {
                get(Integer.parseInt(line[1]) - 1);
            }
        }
    }
}
