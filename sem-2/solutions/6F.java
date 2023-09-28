import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

public class KamilAndStream {
    public static final long MOD = 1_000_000_007;
    public static final int MAX_LOG = 18;

    public static long gcd(long a, long b) {
        return b == 0 ? a : gcd(b, a % b);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(reader.readLine());
        Node[] tree = new Node[n];
        String[] line = reader.readLine().split(" ");
        for (int i = 0; i < n; i++) {
            tree[i] = new Node(i + 1, Long.parseLong(line[i]));
        }
        for (int i = 1; i < n; i++) {
            line = reader.readLine().split(" ");
            int a = Integer.parseInt(line[0]) - 1;
            int b = Integer.parseInt(line[1]) - 1;
            tree[a].children.add(tree[b]);
            tree[b].children.add(tree[a]);
        }
        tree[0].dfs(null, 0);
        for (int level = 1; level <= MAX_LOG; level++) {
            for (Node v : tree) {
                if (v.up[level - 1] != null) {
                    v.up[level] = v.up[level - 1].up[level - 1];
                    if (v.up[level] != null) {
                        v.gcd[level] = gcd(v.gcd[level - 1], v.up[level - 1].gcd[level - 1]);
                    }
                }
            }
        }
        long answer = 0L;
        for (Node v : tree) {
            answer = (answer + v.get_answer(v.value, MAX_LOG, 0)) % MOD;
        }
        System.out.println(answer);
    }

    public static class Node {
        int index, depth;
        long value;
        long[] gcd;
        Node[] up;
        List<Node> children;

        public Node(int index, long value) {
            this.index = index;
            this.value = value;
            gcd = new long[MAX_LOG + 1];
            up = new Node[MAX_LOG + 1];
            children = new ArrayList<>();
        }

        void dfs(Node v, int depth) {
            if (v != null) {
                children.remove(v);
            }
            this.depth = depth;
            up[0] = v;
            if (v != null) {
                gcd[0] = gcd(value, v.value);
            }
            for (Node child : children) {
                child.dfs(this, depth + 1);
            }
        }

        long get_answer(long answer, int maxUp, int prevLen) {
            if (up[0] == null) {
                return (answer * (prevLen + 1)) % MOD;
            }
            while (up[maxUp] == null) {
                maxUp--;
            }
            while (maxUp >= 0 && (answer == 0 ? this.gcd[maxUp] != 0 : this.gcd[maxUp] % answer != 0)) {
                maxUp--;
            }
            if (maxUp == -1) {
                long newLength = prevLen + 1;
                long toAdd = (newLength) * answer;
                return (toAdd + up[0].get_answer(gcd(answer, up[0].value), MAX_LOG, 0)) % MOD;
            }
            return (up[maxUp].get_answer(answer, maxUp, (1 << maxUp) + prevLen)) % MOD;
        }
    }
}
