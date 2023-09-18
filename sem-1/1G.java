import java.io.*;

public class Med {

    public static void quickSort(int[] a, int left, int right) {
        if (left >= right) {
            return;
        }
        int oporElement = a[(left + right) / 2];
        int i = left;
        int j = right;
        while (i <= j) {
            while (a[i] < oporElement) {
                i++;
            }
            while (a[j] > oporElement) {
                j--;
            }
            if (i <= j) {
                int swap = a[i];
                a[i] = a[j];
                a[j] = swap;
                i++;
                j--;
            }
        }
        if (left < j){
            quickSort(a, left, j);
        }
        if (i < right) {
            quickSort(a, i, right);
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String[] first = reader.readLine().split(" ");
        int n = Integer.parseInt(first[0]);
        int m = Integer.parseInt(first[1]);
        int p = Integer.parseInt(first[2]);
        int[] a = new int[n];
        String[] second = reader.readLine().split(" ");
        long liters = 0;
        boolean mesto = true;
        int j = 0;
        for (int i = 0; i < n; i++) {
            int med = Integer.parseInt(second[i]);
            if (med >= p) {
                int r = Math.min(m, med / p);
                liters += p * r;
                m -= r;
                med -= p * r;
                if (med > 0) {
                    a[j] = med;
                    j++;
                }
            } else {
                a[j] = med;
                j++;
            }
            if (m == 0) {
                mesto = false;
                break;
            }
        }
        if (mesto) {
            quickSort(a, 0, j - 1);
            for (int q = j - 1; q >= 0; q--) {
                liters += a[q];
                m--;
                if (m == 0) {
                    break;
                }
            }
            System.out.println(liters);
        } else {
            System.out.println(liters);
        }
    }
}
