import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Levenshtain {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String a = reader.readLine();
        String b = reader.readLine();
        int n = a.length();
        int m = b.length();
        int[][] dp = new int[n + 1][m + 1];
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                if (i == 0 || j == 0) {
                    dp[i][j] = (i == 0) ? j : i;
                } else {
                    if (a.charAt(i - 1) == b.charAt(j - 1)) {
                        dp[i][j] = dp[i - 1][j - 1];
                    } else {
                        dp[i][j] = Math.min(dp[i - 1][j - 1] + 1, dp[i - 1][j] + 1);
                        dp[i][j] = Math.min(dp[i][j], dp[i][j - 1] + 1);
                    }
                }
            }
        }
        System.out.println(dp[n][m]);
    }
}
