import java.io.*;

public class Wsort {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String[] strs = reader.readLine().split(" ");
        int n = Integer.parseInt(strs[0]);
        int m = Integer.parseInt(strs[1]);
        int k = Integer.parseInt(strs[2]);
        String[] words = new String[n];
        for (int i = 0; i < n; i++) {
            words[i] = reader.readLine();
        }
        int alphabet = 26;
        int stop = 0;
        for (int i = m - 1; i >= 0; i--) {
            String[] wss = new String[n];
            int[] chr = new int[alphabet];
            for (int j = 0; j < n; j++) {
                int curChr = words[j].charAt(i) - 97;
                chr[curChr]++;
            }
            int count = 0;
            for (int j = 0; j < alphabet; j++) {
                int swap = chr[j];
                chr[j] = count;
                count += swap;
            }
            for (int j = 0; j < n; j++) {
                int curChr = words[j].charAt(i) - 97;
                wss[chr[curChr]] = words[j];
                chr[curChr]++;
            }
            words = wss;
            stop++;
            if (stop == k) {
                break;
            }
        }
        for (String word : words) {
            System.out.println(word);
        }
    }
}
