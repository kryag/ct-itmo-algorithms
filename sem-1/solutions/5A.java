import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Zaichik {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(reader.readLine());
        String s = reader.readLine();
        int[] dp = new int[n];
        dp[0] = 0;
        for (int i = 1; i < n; i++) {
            if (s.charAt(i) == 'w') {
                dp[i] = -1;
            } else {
                int max = -1;
                if (i - 5 >= 0 && dp[i - 5] != -1) {
                    max = Math.max(max, dp[i - 5]);
                }
                if (i - 3 >= 0 && dp[i - 3] != -1) {
                    max = Math.max(max, dp[i - 3]);
                }
                if (dp[i - 1] != -1) {
                    max = Math.max(max, dp[i - 1]);
                }
                if (max == -1) {
                    dp[i] = -1;
                } else {
                    if (s.charAt(i) == '"') {
                        dp[i] = max + 1;
                    }
                    if (s.charAt(i) == '.') {
                        dp[i] = max;
                    }
                }
            }
        }
        System.out.println(dp[n - 1]);
    }
}
