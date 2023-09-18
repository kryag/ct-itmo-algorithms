import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class TurtleAndCoins {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String[] line = reader.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        int m = Integer.parseInt(line[1]);
        int[][] cell = new int[n][m];
        for (int i = 0; i < n; i++) {
            line = reader.readLine().split(" ");
            for (int j = 0; j < m; j++) {
                cell[i][j] = Integer.parseInt(line[j]);
            }
        }
        int[][] dp = new int[n][m];
        dp[0][0] = cell[0][0];
        for (int j = 1; j < m; j++) {
            dp[0][j] = cell[0][j] + dp[0][j - 1];
        }
        for (int i = 1; i < n; i++) {
            dp[i][0] = cell[i][0] + dp[i - 1][0];
        }
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < m; j++) {
                if (dp[i - 1][j] >= dp[i][j - 1]) {
                    dp[i][j] = cell[i][j] + dp[i - 1][j];
                } else {
                    dp[i][j] = cell[i][j] + dp[i][j - 1];
                }
            }
        }
        System.out.println(dp[n - 1][m - 1]);
        int i = n - 1;
        int j = m - 1;
        StringBuilder result = new StringBuilder();
        while (i != 0 || j != 0) {
            if (i - 1 >= 0 && dp[i][j] - cell[i][j] == dp[i - 1][j]) {
                i--;
                result.append('D');
            } else {
                j--;
                result.append('R');
            }
        }
        System.out.println(result.reverse());
    }
}
