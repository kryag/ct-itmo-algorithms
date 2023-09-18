import java.io.*;

public class CricketField {
    public static int n;
    public static int w;
    public static int h;
    public static int[] xd;
    public static int[] yd;

    public static int[] possibleSquare(int length) {
        int score;
        for (int y = 0; y < h - length + 1; y++) {
            int x = 0;
            while (x < w - length + 1) {
                score = 0;
                for (int tree = 0; tree < n; tree++) {
                    if (xd[tree] < x + length && xd[tree] > x && yd[tree] < y + length && yd[tree] > y) {
                        x = xd[tree];
                        break;
                    }
                    score++;
                }
                if (score == n) {
                    return new int[]{x, y};
                }
            }
        }
        return new int[]{-1, -1};
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String[] line = reader.readLine().split(" ");
        n = Integer.parseInt(line[0]);
        w = Integer.parseInt(line[1]);
        h = Integer.parseInt(line[2]);
        xd = new int[n];
        yd = new int[n];
        for (int i = 0; i < n; i++) {
            String[] derevo = reader.readLine().split(" ");
            xd[i] = Integer.parseInt(derevo[0]);
            yd[i] = Integer.parseInt(derevo[1]);
        }
        int finallyX = 0;
        int finallyY = 0;
        int finallyLength = 0;
        int left = 0;
        int right = Math.min(w, h);
        while (right - left > 5) {
            int median = (left + right) / 2;
            int[] a = possibleSquare(median);
            if (a[0] != -1) {
                finallyX = a[0];
                finallyY = a[1];
                finallyLength = median;
                left = median;
            } else {
                right = median;
            }
        }
        for (int i = right; i >= left; i--) {
            int[] a = possibleSquare(i);
            if (a[0] != -1) {
                finallyX = a[0];
                finallyY = a[1];
                finallyLength = i;
                break;
            }
        }
        System.out.println(finallyX + " " + finallyY + " " + finallyLength);
    }
}
