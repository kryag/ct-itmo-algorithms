import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Fortepiano {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(reader.readLine());
        int[] a = new int[n + 1];
        String[] line = reader.readLine().split(" ");
        for (int i = 0; i < n; i++) {
            a[i + 1] = Integer.parseInt(line[i]);
        }
        int[][] dp = new int[6][n + 1];
        for (int i = 1; i < 6; i++) {
            dp[i][1] = 1;
        }
        for (int i = 2; i < n + 1; i++) {
            if (a[i - 1] < a[i]) {
                for (int j = 1; j < 6; j++) {
                    int s = j - 1;
                    while (s > 0) {
                        if (dp[s][i - 1] == 1) {
                            dp[j][i] = 1;
                            break;
                        }
                        s--;
                    }
                }
            } else if (a[i - 1] > a[i]) {
                for (int j = 1; j < 6; j++) {
                    int s = j + 1;
                    while (s < 6) {
                        if (dp[s][i - 1] == 1) {
                            dp[j][i] = 1;
                            break;
                        }
                        s++;
                    }
                }
            } else {
                for (int j = 1; j < 6; j++) {
                    int s = 1;
                    while (s < 6) {
                        if (dp[s][i - 1] == 1 && s != j) {
                            dp[j][i] = 1;
                            break;
                        }
                        s++;
                    }
                }
            }
        }
        int cur = -1;
        for (int i = 1; i < 6; i++) {
            if (dp[i][n] == 1) {
                cur = i;
                break;
            }
        }
        if (cur == -1) {
            System.out.println(-1);
            return;
        }
        StringBuilder sb = new StringBuilder();
        sb.append(" ").append(cur);
        for (int i = n - 1; i > 0; i--) {
            if (a[i] < a[i + 1]) {
                cur--;
                while (dp[cur][i] != 1) {
                    cur--;
                }
                sb.insert(0, cur);
                sb.insert(0, " ");
            } else if (a[i] > a[i + 1]) {
                cur++;
                while (dp[cur][i] != 1) {
                    cur++;
                }
                sb.insert(0, cur);
                sb.insert(0, " ");
            } else {
                int newCur = 1;
                while (true) {
                    if (dp[newCur][i] == 1 && newCur != cur) {
                        cur = newCur;
                        break;
                    }
                    newCur++;
                }
                sb.insert(0, cur);
                sb.insert(0, " ");
            }
        }
        sb.delete(0, 1);
        System.out.println(sb);
    }
}
