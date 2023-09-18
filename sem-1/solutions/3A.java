import java.io.*;

public class BinarySearch {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String[] line1 = reader.readLine().split(" ");
        String[] line2 = reader.readLine().split(" ");
        String[] line3 = reader.readLine().split(" ");
        reader.close();

        int n = Integer.parseInt(line1[0]);
        int k = Integer.parseInt(line1[1]);
        int[] a = new int[n];
        for (int i = 0; i < n; i++) {
            a[i] = Integer.parseInt(line2[i]);
        }

        int t = 0;
        while (t < k) {
            int l = -1;
            int r = n;
            int findElement = Integer.parseInt(line3[t]);
            if (findElement < a[0] || findElement > a[n - 1]) {
                System.out.println("NO");
            } else {
                while (r > l + 1) {
                    int m = (r + l) / 2;
                    if (a[m] <= findElement) {
                        l = m;
                    } else {
                        r = m;
                    }
                }
                if (a[l] == findElement) {
                    System.out.println("YES");
                } else {
                    System.out.println("NO");
                }
            }
            t++;
        }
    }
}
