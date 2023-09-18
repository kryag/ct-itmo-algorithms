import java.io.*;

public class Sortset {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String[] first = reader.readLine().split(" ");
        int n = Integer.parseInt(first[0]);
        int m = Integer.parseInt(first[1]);
        int k = Integer.parseInt(first[2]);
        String[] strs = new String[k];
        for (int i = 0; i < k; i++) {
            strs[i] = reader.readLine();
        }
        boolean flag = true;
        for (int i = 0; i < (1 << n); i++) {
            int[] a = new int[n];
            for (int j = 0; j < n; j++) {
                a[j] = (i >> j) & 1;
            }
            for (int j = 0; j < k; j++) {
                String[] str = strs[j].split(" ");
                int r = Integer.parseInt(str[0]);
                for (int o = 0; o < r; o++) {
                    int max = Math.max(a[Integer.parseInt(str[1 + 2 * o]) - 1], a[Integer.parseInt(str[2 + 2 * o]) - 1]);
                    int min = Math.min(a[Integer.parseInt(str[1 + 2 * o]) - 1], a[Integer.parseInt(str[2 + 2 * o]) - 1]);
                    a[Math.min(Integer.parseInt(str[1 + 2 * o]) - 1, Integer.parseInt(str[2 + 2 * o]) - 1)] = min;
                    a[Math.max(Integer.parseInt(str[1 + 2 * o]) - 1, Integer.parseInt(str[2 + 2 * o]) - 1)] = max;
                }
            }
            for (int j = 0; j < a.length - 1; j++) {
                if (a[j] > a[j+1]) {
                    flag = false;
                    break;
                }
            }
            if (!flag) {
                break;
            }
        }
        if (flag) {
            System.out.println("Yes");
        } else {
            System.out.println("No");
        }
    }
}
