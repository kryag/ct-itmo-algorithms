import java.io.*;

public class CountInversions {
    private static long countInversions;

    public static int[] sort(int[] a) {
        countInversions = 0;
        return sort(a, 0, a.length - 1);
    }

    static int[] sort(int[] a, int left, int right) {
        if (left > right - 1) {
            return new int[]{a[left]};
        }
        int mid = left + (right - left) / 2;
        return merge(sort(a, left, mid), sort(a, mid + 1, right));
    }

    static int[] merge(int[] a, int[] b) {
        int[] m = new int[a.length + b.length];
        int aPos = 0;
        int bPos = 0;
        int mPos = 0;
        while ((aPos < a.length) && (bPos < b.length)) {
            if (a[aPos] <= b[bPos]) {
                m[mPos++] = a[aPos++];
            } else {
                m[mPos++] = b[bPos++];
                countInversions += (a.length - aPos);
            }
        }
        while (aPos < a.length) {
            m[mPos++] = a[aPos++];
        }
        while (bPos < b.length) {
            m[mPos++] = b[bPos++];
        }
        return m;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(reader.readLine());
        int[] a = new int[n];
        String[] strs = reader.readLine().split(" ");
        for (int i = 0; i < n; i++) {
            a[i] = Integer.parseInt(strs[i]);
        }
        sort(a);
        System.out.println(countInversions);
    }
}
