import java.io.*;

public class Otrezki {
    public static long[] prefSum;
    public static int n;
    public static long k;
    public static long countSubarrays;

    public static void countingSubarrays(int left, int right) {
        if (left == right) {
            if (prefSum[left] >= k) {
                countSubarrays++;
            }
        } else {
            int mid = (left + right) / 2;
            countingSubarrays(left, mid);
            countingSubarrays(mid + 1, right);
            long[] help = new long[right - left + 1];
            int first = left;
            int second = mid + 1;
            while ((first <= mid) && (second <= right)) {
                if (prefSum[second] - prefSum[first] < k) {
                    if (second >= right) {
                        first++;
                    } else {
                        second++;
                    }
                } else {
                    countSubarrays += right - second + 1;
                    if (first < mid) {
                        first++;
                    } else {
                        break;
                    }
                }
            }
            first = left;
            second = mid + 1;
            for (int i = 0; i < right - left + 1; i++) {
                if (first <= mid) {
                    if (second > right) {
                        help[i] = prefSum[first];
                        first++;
                    } else {
                        if (prefSum[first] > prefSum[second]) {
                            help[i] = prefSum[second];
                            second++;
                        } else {
                            help[i] = prefSum[first];
                            first++;
                        }
                    }
                } else {
                    help[i] = prefSum[second];
                    second++;
                }
            }
            if (right + 1 - left >= 0) {
                System.arraycopy(help, 0, prefSum, left, right + 1 - left);
            }
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String[] nk = reader.readLine().split(" ");
        String[] line = reader.readLine().split(" ");
        n = Integer.parseInt(nk[0]);
        k = Long.parseLong(nk[1]);
        prefSum = new long[n];
        prefSum[0] = Long.parseLong(line[0]);
        for (int i = 1; i < n; i++) {
            prefSum[i] = prefSum[i - 1] + Integer.parseInt(line[i]);
        }
        countingSubarrays(0, n - 1);
        System.out.println(countSubarrays);
    }
}
