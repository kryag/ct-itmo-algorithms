import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Backpack01 {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String[] line = reader.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        int m = Integer.parseInt(line[1]);
        int[] a = new int[n + 1];
        line = reader.readLine().split(" ");
        for (int i = 0; i < n; i++) {
            a[i + 1] = Integer.parseInt(line[i]);
        }
        int[][] dp = new int[n + 1][m + 1];
        dp[0][0] = 1;
        for (int i = 1; i < n + 1; i++) {
            for (int j = 0; j < m + 1; j++) {
                dp[i][j] = dp[i - 1][j];
                if (j - a[i] >= 0 && dp[i][j] == 0) {
                    dp[i][j] = dp[i - 1][j - a[i]];
                }
            }
        }
        for (int i = m; i >= 0; i--) {
            if (dp[n][i] == 1) {
                System.out.println(i);
                break;
            }
        }
    }
}
