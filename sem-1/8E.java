import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class Giri3 {
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
        if (sum % 3 != 0) {
            System.out.println(-1);
            return;
        }
        List<List<Set<Integer>>> dp = new ArrayList<>(sum / 3 + 1);
        for (int i = 0; i < sum / 3 + 1; i++) {
            List<Set<Integer>> temp = new ArrayList<>();
            for (int j = 0; j < n - 1; j++) {
                Set<Integer> temp2 = new HashSet<>();
                temp.add(temp2);
            }
            dp.add(temp);
        }
        for (int i = 1; i < n + 1; i++) {
            if (a[i] <= sum / 3 && dp.get(a[i]).get(1).isEmpty()) {
                dp.get(a[i]).get(1).add(i);
            }
        }
        for (int i = 2; i < n - 1; i++) {
            for (int j = 1; j < sum / 3 + 1; j++) {
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
        for (int s = 0; s < n - 1; s++) {
            if (!dp.get(sum / 3).get(s).isEmpty()) {
                List<List<Set<Integer>>> dp2 = new ArrayList<>(sum / 3 + 1);
                for (int i = 0; i < sum / 3 + 1; i++) {
                    List<Set<Integer>> temp = new ArrayList<>();
                    for (int j = 0; j < n - dp.get(sum / 3).get(s).size(); j++) {
                        Set<Integer> temp2 = new HashSet<>();
                        temp.add(temp2);
                    }
                    dp2.add(temp);
                }
                for (int i = 1; i < n + 1; i++) {
                    if (a[i] <= sum / 3 && !dp.get(sum / 3).get(s).contains(i) && dp2.get(a[i]).get(1).isEmpty()) {
                        dp2.get(a[i]).get(1).add(i);
                    }
                }
                for (int i = 2; i < n - dp.get(sum / 3).get(s).size(); i++) {
                    for (int j = 1; j < sum / 3 + 1; j++) {
                        for (int p = 1; p < n + 1; p++) {
                            if (j - a[p] > 0 && !dp2.get(j - a[p]).get(i - 1).isEmpty()) {
                                if (!dp2.get(j - a[p]).get(i - 1).contains(p) && !dp.get(sum / 3).get(s).contains(p)) {
                                    Set<Integer> temp = new HashSet<>(dp2.get(j - a[p]).get(i - 1));
                                    temp.add(p);
                                    List<Set<Integer>> temp2 = new ArrayList<>(dp2.get(j));
                                    temp2.set(i, temp);
                                    dp2.set(j, temp2);
                                    break;
                                }
                            }
                        }
                    }
                }
                for (int i = 0; i < dp2.get(sum / 3).size(); i++) {
                    if (!dp2.get(sum / 3).get(i).isEmpty()) {
                        StringBuilder first = new StringBuilder();
                        StringBuilder second = new StringBuilder();
                        StringBuilder third = new StringBuilder();
                        for (int q = 1; q < n + 1; q++) {
                            if (dp.get(sum / 3).get(s).contains(q)) {
                                first.append(q).append(" ");
                            } else {
                                if (dp2.get(sum / 3).get(i).contains(q)) {
                                    second.append(q).append(" ");
                                } else {
                                    third.append(q).append(" ");
                                }
                            }
                        }
                        first.setLength(first.length() - 1);
                        second.setLength(second.length() - 1);
                        third.setLength(third.length() - 1);
                        System.out.println(dp.get(sum / 3).get(s).size() + " " + first);
                        System.out.println(dp2.get(sum / 3).get(i).size() + " " + second);
                        System.out.println((n - dp.get(sum / 3).get(s).size() - dp2.get(sum / 3).get(i).size()) + " " + third);
                        return;
                    }
                }
            }
        }
        System.out.println(-1);
    }
}
