import java.io.*;

public class Wires {
    public static int k;
    public static int n;
    public static int[] a;

    public static boolean isCorrect(int segmentLength) {
        int count = 0;
        for (int i = 0; i < n; i++) {
            count += a[i] / segmentLength;
            if (count >= k) {
                return true;
            }
        }
        return false;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String[] line1 = reader.readLine().split(" ");
        n = Integer.parseInt(line1[0]);
        k = Integer.parseInt(line1[1]);
        a = new int[n];
        int max = 0;
        int min = 0;
        for (int i = 0; i < n; i++) {
            a[i] = Integer.parseInt(reader.readLine());
            if (a[i] > max) {
                max = a[i];
            }
            if (a[i] < min) {
                min = a[i];
            }
        }
        reader.close();

        int result = 0;
        int l = min;
        int r = max;
        while (r - l > 10) {
            int median = (l + r) / 2;
            if (isCorrect(median)) {
                l = median;
                result = l;
            } else {
                r = median;
            }
        }
        for (int i = Math.max(l, 1); i <= r; i++) {
            if (isCorrect(i)) {
                result = i;
            }
        }
        System.out.println(result);
    }
}
