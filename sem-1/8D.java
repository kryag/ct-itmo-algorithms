import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class Giri2 {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(reader.readLine());
        String[] line = reader.readLine().split(" ");
        int[] a = new int[n + 1];
        int sum = 0;
        for (int i = 0; i < n; i++) {
            a[i + 1] = Integer.parseInt(line[i]);
            sum += a[i + 1];
        }
        if (n % 2 == 1 || sum % 2 == 1) {
            System.out.println(-1);
            return;
        }
        List<List<Set<Integer>>> dp = new ArrayList<>(sum / 2 + 1);
        for (int i = 0; i < sum / 2 + 1; i++) {
            List<Set<Integer>> temp = new ArrayList<>();
            for (int j = 0; j < n / 2 + 1; j++) {
                Set<Integer> temp2 = new HashSet<>();
                temp.add(temp2);
            }
            dp.add(temp);
        }
        for (int i = 1; i < n + 1; i++) {
            if (a[i] <= sum / 2 && dp.get(a[i]).get(1).isEmpty()) {
                dp.get(a[i]).get(1).add(i);
            }
        }
        for (int i = 2; i < n / 2 + 1; i++) {
            for (int j = 1; j < sum / 2 + 1; j++) {
                for (int p = 1; p < n + 1; p++) {
                    if (j - a[p] > 0 && !dp.get(j - a[p]).get(i - 1).isEmpty()) {
                        if (!dp.get(j - a[p]).get(i - 1).contains(p)) {
                            Set<Integer> temp = new HashSet<>(dp.get(j - a[p]).get(i - 1));
                            temp.add(p);
                            List<Set<Integer>> temp2 = new ArrayList<>(dp.get(j));
                            temp2.set(i, temp);
                            dp.set(j, temp2);
                            break;
                        }
                    }
                }
            }
        }
        if (dp.get(sum / 2).get(n / 2).isEmpty()) {
            System.out.println(-1);
            return;
        }
        StringBuilder first = new StringBuilder();
        StringBuilder second = new StringBuilder();
        for (int i = 1; i < n + 1; i++) {
            if (dp.get(sum / 2).get(n / 2).contains(i)) {
                first.append(i).append(" ");
            } else {
                second.append(i).append(" ");
            }
        }
        first.setLength(first.length() - 1);
        second.setLength(second.length() - 1);
        System.out.println(first);
        System.out.println(second);
    }
}
