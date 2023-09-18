import java.io.*;

public class AntiQuickSort {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(reader.readLine());
        int[] a = new int[n];
        for (int i = 0; i < n; i++) {
            a[i] = i + 1;
        }
        for (int i = 2; i < n; i++) {
            int swap = a[i];
            a[i] = a[i/2];
            a[i/2] = swap;
        }
        System.out.print(a[0]);
        for (int i = 1; i < n; i++) {
            System.out.print(" " + a[i]);
        }
    }
}
