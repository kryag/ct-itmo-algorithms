import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Bankomat {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(reader.readLine());
        int[] w = new int[n + 1];
        String[] line = reader.readLine().split(" ");
        for (int i = 0; i < n; i++) {
            w[i] = Integer.parseInt(line[i]);
        }
        int s = Integer.parseInt(reader.readLine());
        int[] dp = new int[s + 1];
        for (int i = 0; i < s + 1; i++) {
            dp[i] = s + 1;
        }
        dp[0] = 0;
        for (int i = 1; i < s + 1; i++) {
            for (int j = 0; j < n; j++) {
                if (w[j] <= i) {
                    dp[i] = Math.min(dp[i], dp[i - w[j]] + 1);
                }
            }
        }
        if (dp[s] > s) {
            System.out.println(-1);
        } else {
            System.out.println(dp[s]);
            StringBuilder sb = new StringBuilder();
            int i = s;
            while (i != 0) {
                int minValue = s + 1;
                int minIndex = -1;
                for (int j = 0; j < n; j++) {
                    if (w[j] <= i) {
                        if (dp[i - w[j]] < minValue && dp[i - w[j]] != s + 1) {
                            minIndex = j;
                            minValue = dp[i - w[j]];
                        }
                    }
                }
                sb.append(w[minIndex]).append(" ");
                i -= w[minIndex];
            }
            sb.setLength(sb.length() - 1);
            System.out.println(sb);
        }
    }
}
