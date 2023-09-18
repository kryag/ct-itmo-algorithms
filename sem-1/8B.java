import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Backpack {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String[] line = reader.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        int m = Integer.parseInt(line[1]);
        int[] w = new int[n + 1];
        line = reader.readLine().split(" ");
        for (int i = 0; i < n; i++) {
            w[i + 1] = Integer.parseInt(line[i]);
        }
        int[] c = new int[n + 1];
        line = reader.readLine().split(" ");
        for (int i = 0; i < n; i++) {
            c[i + 1] = Integer.parseInt(line[i]);
        }
        int[][] dp = new int[n + 1][m + 1];
        dp[0][0] = 0;
        for (int i = 1; i < m + 1; i++) {
            dp[0][i] = Integer.MIN_VALUE;
        }
        for (int i = 1; i < n + 1; i++) {
            for (int j = 0; j < m + 1; j++) {
                dp[i][j] = dp[i - 1][j];
                if (j - w[i] >= 0 && dp[i - 1][j - w[i]] != Integer.MIN_VALUE) {
                    dp[i][j] = Math.max(dp[i - 1][j - w[i]] + c[i], dp[i][j]);
                }
            }
        }
        int result = Integer.MIN_VALUE;
        int ind = 0;
        for (int i = 0; i < m + 1; i++) {
            if (dp[n][i] > result) {
                result = dp[n][i];
                ind = i;
            }
        }
        int count = 0;
        int i = n;
        StringBuilder sb = new StringBuilder();
        do {
            if (ind - w[i] >= 0 && dp[i - 1][ind] <= dp[i - 1][ind - w[i]] + c[i]) {
                count++;
                sb.insert(0, i);
                sb.insert(0, " ");
                ind -= w[i];
            }
            i--;
        } while (i != 0);
        System.out.println(count);
        System.out.println(sb.delete(0, 1));
    }
}
