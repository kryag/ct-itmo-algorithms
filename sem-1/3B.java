import java.io.*;

public class LeftAndRightBinarySearch {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String[] line1 = reader.readLine().split(" ");
        String[] line2 = reader.readLine().split(" ");
        String[] line3 = reader.readLine().split(" ");
        reader.close();

        int n = Integer.parseInt(line1[0]);
        int m = Integer.parseInt(line1[1]);
        long[] a = new long[n];
        for (int i = 0; i < n; i++) {
            a[i] = Integer.parseInt(line2[i]);
        }

        int t = 0;
        while (t < m) {
            int l = -1;
            int r = n;
            long findElement = Long.parseLong(line3[t]);
            while (r > l + 1) {
                int med = (l + r) / 2;
                if (a[med] < findElement) {
                    l = med;
                } else {
                    r = med;
                }
            }
            if (r == n || findElement < a[0] || a[r] != findElement) {
                System.out.println("0");
            } else {
                int fOut = r + 1;
                l = -1;
                r = n;
                while (r > l + 1) {
                    int med = (l + r) / 2;
                    if (a[med] <= findElement) {
                        l = med;
                    } else {
                        r = med;
                    }
                }
                int sOut = l + 1;
                System.out.println(fOut + " " + sOut);
            }
            t++;
        }
    }
}
