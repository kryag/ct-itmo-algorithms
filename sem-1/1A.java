import java.io.*;

public class QuickSort {

    public static void quickSort(int[] a, int left, int right) {
        if (left >= right)
            return;
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
        if (left < j)
            quickSort(a, left, j);
        if (i < right)
            quickSort(a, i, right);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(reader.readLine());
        int[] a = new int[n];
        String[] strs = reader.readLine().split(" ");
        for (int i = 0; i < n; i++) {
            a[i] = Integer.parseInt(strs[i]);
        }
        quickSort(a, 0, n - 1);
        for (int i = 0; i < n; i++) {
            System.out.print(a[i] + " ");
        }
    }
}
