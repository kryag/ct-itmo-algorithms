import java.io.*;
import java.util.Stack;

public class Colonizators2 {

    public static void f(int[] a, int[] first, boolean[] firstFlag, Stack<Integer> stValue, Stack<Integer> stIndex, int i) {
        while (!stValue.empty() && a[i] >= stValue.peek()) {
            stValue.pop();
            stIndex.pop();
        }
        if (stValue.empty()) {
            first[i] = 0;
        } else {
            if (a[i] > 0) {
                first[stIndex.peek()]++;
                firstFlag[i] = true;
            }
        }
        if (a[i] > 0) {
            stValue.push(a[i]);
            stIndex.push(i);
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(reader.readLine());
        int[] a = new int[n];
        String[] line = reader.readLine().split(" ");
        for (int i = 0; i < n; i++) {
            a[i] = Integer.parseInt(line[i]);
        }
        int[] first = new int[n];
        boolean[] firstFlag = new boolean[n];
        Stack<Integer> stValue = new Stack<>();
        Stack<Integer> stIndex = new Stack<>();
        for (int i = n - 1; i >= 0; i--) {
            f(a, first, firstFlag, stValue, stIndex, i);
        }
        for (int i = 0; i < n; i++) {
            if (firstFlag[i]) {
                a[i]--;
            }
            a[i] += first[i];
        }
        stValue.clear();
        stIndex.clear();
        int[] second = new int[n];
        boolean[] secondFlag = new boolean[n];
        for (int i = 0; i < n; i++) {
            f(a, second, secondFlag, stValue, stIndex, i);
        }
        int maxCards = 0;
        for (int i = 0; i < n; i++) {
            if (secondFlag[i]) {
                a[i]--;
            }
            a[i] += second[i];
            if (a[i] > maxCards) {
                maxCards = a[i];
            }
        }
        System.out.println(maxCards);
    }
}
