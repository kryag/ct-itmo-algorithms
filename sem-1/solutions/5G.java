import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class kriper2004 {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String s = reader.readLine();
        int n = Integer.parseInt(reader.readLine());
        boolean flag = true;
        for (int i = 0; i < s.length() - 1; i++) {
            if ((int) s.charAt(i) + 1 == (int) s.charAt(i + 1)) {
                System.out.println(0);
                flag = false;
                break;
            }
        }
        if (flag) {
            if (s.length() == n) {
                System.out.println(1);
            } else {
                int[][] dp = new int[n][26];
                dp[s.length() - 1][s.charAt(s.length() - 1) - 97] = 1;
                for (int i = s.length(); i < n; i++) {
                    for (int j = 0; j < 26; j++) {
                        for (int q = 0; q < 26; q++) {
                            if (q + 1 != j) {
                                dp[i][j] = (dp[i][j] + dp[i - 1][q]) % 998244353;
                            }
                        }
                    }
                }
                int result = 0;
                for (int i = 0; i < 26; i++) {
                    result += dp[n - 1][i];
                    result %= 998244353;
                }
                System.out.println(result);
            }
        }
    }
}
