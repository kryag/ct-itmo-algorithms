import java.io.*;
import java.util.*;

public class Histogramm {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String[] line = reader.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        int[] a = new int[n];
        for (int i = 0; i < n; i++) {
            a[i] = Integer.parseInt(line[i + 1]);
        }
        int[] len = new int[n];
        long curProd;
        long maxProd = 0;
        Stack<Integer> value = new Stack<>();
        Stack<Integer> ind = new Stack<>();
        int size = 0;
        int temp = 0;
        for (int i = 0; i < n; i++) {
            while (size != 0 && a[i] <= value.peek()) {
                value.pop();
                ind.pop();
                size--;
            }
            if (size > 0) {
                temp = ind.peek();
            }
            value.push(a[i]);
            ind.push(i);
            size++;
            if (size == 1) {
                len[i] = i;
            } else {
                len[i] = i - temp - 1;
            }
        }
        value.clear();
        ind.clear();
        size = 0;
        for (int i = n - 1; i >= 0; i--) {
            while (size != 0 && a[i] <= value.peek()) {
                value.pop();
                ind.pop();
                size--;
            }
            if (size > 0) {
                temp = ind.peek();
            }
            value.push(a[i]);
            ind.push(i);
            size++;
            if (size == 1) {
                len[i] = len[i] + n - i;
            } else {
                len[i] = len[i] + temp - i;
            }
        }
        for (int i = 0; i < n; i++) {
            curProd = (long) a[i] * len[i];
            maxProd = Math.max(maxProd, curProd);
        }
        System.out.println(maxProd);
    }
}
