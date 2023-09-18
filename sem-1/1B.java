import java.io.*;

public class KStatistic {

    public static int split(int[] a, int l, int r) {
        int x = a[r];
        int i = l;
        for (int j = l; j < r; j++) {
            if (a[j] <= x) {
                int swap = a[i];
                a[i] = a[j];
                a[j] = swap;
                i++;
            }
        }
        int swap = a[i];
        a[i] = a[r];
        a[r] = swap;
        return i;
    }

    public static int kStat(int[] a, int l, int r, int k) {
        int m = split(a, l, r);
        if (m - l == k - 1) {
            return a[m];
        }
        if (m - l > k - 1) {
            return kStat(a, l, m - 1, k);
        }
        return kStat(a, m + 1, r, k - m + l - 1);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String[] strs = reader.readLine().split(" ");
        int n = Integer.parseInt(strs[0]);
        int[] a = new int[n];
        a[0] = Integer.parseInt(strs[1]);
        int k = Integer.parseInt(strs[2]);
        for (int i = 1; i < n; i++) {
            a[i] = (int) ((1_103_515_245 * (long)(a[i - 1]) + 12345) % 2147483648L);
        }
        System.out.println(kStat(a, 0, n - 1, k + 1));
    }
}
