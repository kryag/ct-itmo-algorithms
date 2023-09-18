import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class LCS {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(reader.readLine());
        int[] a = new int[n];
        String[] line = reader.readLine().split(" ");
        for (int i = 0; i < n; i++) {
            a[i] = Integer.parseInt(line[i]);
        }
        int m = Integer.parseInt(reader.readLine());
        int[] b = new int[m];
        line = reader.readLine().split(" ");
        for (int i = 0; i < m; i++) {
            b[i] = Integer.parseInt(line[i]);
        }
        int[][] dp = new int[n][m];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (a[i] == b[j]) {
                    dp[i][j] = ((i - 1 >= 0 && j - 1 >= 0) ? dp[i - 1][j - 1] : 0) + 1;
                } else {
                    if (i - 1 >= 0) {
                        if (j - 1 >= 0) {
                            dp[i][j] = Math.max(dp[i - 1][j], dp[i][j - 1]);
                        } else {
                            dp[i][j] = dp[i - 1][j];
                        }
                    } else {
                        if (j - 1 >= 0) {
                            dp[i][j] = dp[i][j - 1];
                        } else {
                            dp[i][j] = 0;
                        }
                    }
                }
            }
        }
        int i = n - 1;
        int j = m - 1;
        StringBuilder result = new StringBuilder();
        while (i >= 0 || j >= 0) {
            if (i >= 0 && j >= 0 && a[i] == b[j]) {
                result.insert(0, a[i]);
                result.insert(0, " ");
                i--;
                j--;
            } else {
                if (i - 1 >= 0) {
                    if (j - 1 >= 0) {
                        if (dp[i - 1][j] >= dp[i][j - 1]) {
                            i--;
                        } else {
                            j--;
                        }
                    } else {
                        i--;
                    }
                } else {
                    if (j - 1 >= 0) {
                        j--;
                    } else {
                        break;
                    }
                }
            }
        }
        System.out.println(dp[n - 1][m - 1]);
        result.delete(0, 1);
        System.out.println(result);
    }
}
