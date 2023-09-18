import java.io.*;

public class Garland {
    public static int n;
    public static double[] a;

    public static boolean isCorrect(double h) {
        a[1] = h;
        for (int i = 2; i < n; i++) {
            a[i] = 2 * a[i - 1] - a[i - 2] + 2;
        }
        for (int i = 0; i < n; i++) {
            if (a[i] <= 0) {
                return false;
            }
        }
        return true;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String[] line = reader.readLine().split(" ");
        n = Integer.parseInt(line[0]);
        a = new double[n];
        a[0] = Double.parseDouble(line[1]);

        double l = 0;
        double r = 2000;
        for (int i = 0; i < 1000; i++) {
            double mid = (l + r) / 2;
            if (isCorrect(mid)) {
                r = mid;
            } else {
                l = mid;
            }
        }
        isCorrect(r);
        System.out.printf("%.2f", a[n - 1]);
    }
}
