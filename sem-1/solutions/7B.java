import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class CuttingGraph {
    public static int[] p;

    public static int find(int x) {
        if (p[x] != x) {
            p[x] = find(p[x]);
        }
        return p[x];
    }

    public static void join(int x, int y) {
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
        int m = Integer.parseInt(line[1]);
        int k = Integer.parseInt(line[2]);
        p = new int[n];
        for (int i = 0; i < n; i++) {
            p[i] = i;
        }
        String[] answers = new String[k - m];
        for (int i = 0; i < m; i++) {
            reader.readLine();
        }
        String[] action = new String[k];
        for (int i = 0; i < k; i++) {
            action[k - i - 1] = reader.readLine();
        }
        int count = 0;
        for (int i = 0; i < k; i++) {
            String[] s = action[i].split(" ");
            if (s[0].equals("ask")) {
                if (ask(Integer.parseInt(s[1]) - 1, Integer.parseInt(s[2]) - 1)) {
                    answers[k - m - count - 1] = "YES";
                } else {
                    answers[k - m - count - 1] = "NO";
                }
                count++;
            } else {
                join(Integer.parseInt(s[1]) - 1, Integer.parseInt(s[2]) - 1);
            }
        }
        for (String s : answers) {
            System.out.println(s);
        }
    }
}
