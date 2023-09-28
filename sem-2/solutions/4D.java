import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashSet;
import java.util.Set;

public class HashCode {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int k = Integer.parseInt(reader.readLine());
        StringBuilder first = new StringBuilder("a".repeat(k));
        Set<String> words = new HashSet<>(Set.of(first.toString()));
        for (int i = 0; i <= k - 2; i++) {
            StringBuilder sb = new StringBuilder(first);
            sb.setCharAt(i, 'b');
            sb.setCharAt(i + 1, 'B');
            words.add(sb.toString());
        }
        for (String s : words) {
            System.out.println(s);
        }
    }
}
