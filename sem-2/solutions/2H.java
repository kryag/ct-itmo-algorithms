import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;

public class Pictures {
    public static final int MOD = 10_007;
    public static int[][] tree;
    public static int[] col;
    public static int[] bw;
    public static int n;
    public static int c;

    public static void update(int v) {
        for (int i = 0; i <= c; i++) {
            tree[v][i] = 0;
        }
        for (int i = 0; i <= c; i++) {
            for (int j = 0; j <= c; j++) {
                int tmp = Math.min(i + j, c);
                tree[v][tmp] += (tree[v * 2][i] * tree[v * 2 + 1][j]) % MOD;
            }
        }
        for (int i = 0; i <= c; i++) {
            tree[v][i] %= MOD;
        }
    }

    public static void set(int v) {
        v += n;
        Arrays.fill(tree[v], 0);
        tree[v][0] = bw[v - n] % MOD;
        tree[v][1] = col[v - n] % MOD;
        v /= 2;
        for (int i = v; i > 0; i /= 2) {
            update(i);
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String[] line = reader.readLine().split(" ");
        n = Integer.parseInt(line[0]);
        c = Integer.parseInt(line[1]);
        col = new int[n];
        bw = new int[n];
        tree = new int[2 * n][c + 1];

        line = reader.readLine().split(" ");
        for (int i = 0; i < n; i++) {
            col[i] = Integer.parseInt(line[i]);
        }

        line = reader.readLine().split(" ");
        for (int i = 0; i < n; i++) {
            bw[i] = Integer.parseInt(line[i]);
        }

        for (int i = 0; i < n; i++) {
            tree[n + i][0] = bw[i] % MOD;
            tree[n + i][1] = col[i] % MOD;
        }
        for (int i = n - 1; i >= 1; i--) {
            update(i);
        }

        int q = Integer.parseInt(reader.readLine());
        while (q-- > 0) {
            line = reader.readLine().split(" ");
            int change = Integer.parseInt(line[0]) - 1;
            col[change] = Integer.parseInt(line[1]);
            bw[change] = Integer.parseInt(line[2]);
            set(change);
            System.out.println(tree[1][c]);
        }
    }
}
