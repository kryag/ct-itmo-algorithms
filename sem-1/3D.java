import java.io.*;
import java.util.*;

public class KBest {
    public static int n;
    public static int k;
    public static ArrayList<Integer> v;
    public static ArrayList<Integer> w;

    public static double sumK(double median) {
        ArrayList<Double> list1 = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            list1.add(v.get(i) - median * w.get(i));
        }
        mergesort(list1, 0, n);
        double sumK = 0;
        for (int i = n - 1; i >= n - k; i--) {
            sumK += list1.get(i);
        }
        return sumK;
    }

    public static void merge(ArrayList<Double> list1, int left, int median, int right) {
        ArrayList<Double> temp = new ArrayList<>();
        for (int k = 0, j = median, i = left; k < right - left; k++) {
            if (j == right || (i < median && list1.get(i) < list1.get(j))) {
                temp.add(list1.get(i));
                i++;
            } else {
                temp.add(list1.get(j));
                j++;
            }
        }
        for (int t = left, p = 0; t < right; t++, p++) {
            list1.set(t, temp.get(p));
        }
    }

    public static void mergesort(ArrayList<Double> list1, int left, int right) {
        if (right - left < 2) {
            return;
        }
        int median = (left + right) / 2;
        mergesort(list1, left, median);
        mergesort(list1, median, right);
        merge(list1, left, median, right);
    }


    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String[] nk = reader.readLine().split(" ");
        n = Integer.parseInt(nk[0]);
        k = Integer.parseInt(nk[1]);
        double right = Integer.MIN_VALUE;
        v = new ArrayList<Integer>();
        w = new ArrayList<Integer>();
        for (int i = 0; i < n; i++) {
            String[] line = reader.readLine().split(" ");
            v.add(Integer.parseInt(line[0]));
            w.add(Integer.parseInt(line[1]));
            if ((double) v.get(i) / w.get(i) > right) {
                right = (double) v.get(i) / w.get(i);
            }
        }
        reader.close();
        right += 1;
        double left = -1;
        while (right - left > 0.00001)  {
            double median = (left + right) / 2;
            if (sumK(median) <= 0) {
                right = median;
            } else {
                left = median;
            }
        }
        ArrayList<Double> list1 = new ArrayList<>();
        ArrayList<Double> list2 = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            list1.add(v.get(i) - right * w.get(i));
            list2.add(v.get(i) - right * w.get(i));
        }
        mergesort(list2, 0, n);
        int count = 0;
        int countMin = 0;
        double min = list2.get(n - k);
        for (int i = n - k; i < n; i++) {
            if (list2.get(i) != min) {
                break;
            }
            count++;
        }
        for (int i = 0; i < n; i++) {
            if (list1.get(i) > min || (list1.get(i) == min && countMin < count)) {
                System.out.print((i + 1) + " ");
            }
            if (list1.get(i) == min) {
                countMin++;
            }
        }
    }
}
