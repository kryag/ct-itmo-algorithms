import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class LIS {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(reader.readLine());
        int[] a = new int[n];
        String[] line = reader.readLine().split(" ");
        for (int i = 0; i < n; i++) {
            a[i] = Integer.parseInt(line[i]);
        }
        int[] dp = new int[n];
        int[] prev = new int[n];
        dp[0] = 1;
        prev[0] = -1;
        int max;
        int ind;
        for (int i = 1; i < n; i++) {
            max = 0;
            ind = -1;
            for (int j = 0; j < i; j++) {
                if (a[j] < a[i] && dp[j] > max) {
                    max = dp[j];
                    ind = j;
                }
            }
            dp[i] = max + 1;
            prev[i] = ind;
        }
        max = 0;
        ind = 0;
        for (int i = 0; i < n; i++) {
            if (dp[i] > max) {
                max = dp[i];
                ind = i;
            }
        }
        StringBuilder result = new StringBuilder();
        result.insert(0, a[ind]);
        result.insert(0, " ");
        ind = prev[ind];
        while (ind != -1) {
            result.insert(0, a[ind]);
            result.insert(0, " ");
            ind = prev[ind];
        }
        System.out.println(max);
        result.delete(0, 1);
        System.out.println(result);
    }
}
