import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

public class AandBandAudiences {
    public static Node[] tree;
    public static int[][] up;
    public static int[] logs;

    public static void dfs(int v, int depth) {
        tree[v].depth = depth;
        for (int n : tree[v].neighbours) {
            if (n != tree[v].parent) {
                tree[n].parent = v;
                dfs(n, depth + 1);
                tree[v].size += tree[n].size;
            }
        }
    }

    public static void calculateLogs(int n) {
        logs = new int[n + 1];
        for (int i = 2; i < n + 1; i++) {
            logs[i] = logs[i / 2] + 1;
        }
    }

    public static void calculateBinaryLifts() {
        up = new int[logs[tree.length] + 1][tree.length];
        for (int v = 0; v < tree.length; v++) {
            up[0][v] = tree[v].parent;
        }
        for (int k = 1; k < up.length; k++) {
            for (int v = 0; v < tree.length; v++) {
                up[k][v] = up[k - 1][up[k - 1][v]];
            }
        }
    }

    public static int[] getLCA(int u, int v) {
        if (u == v) {
            return new int[]{u, u, u};
        }
        if (tree[u].depth < tree[v].depth) {
            int temp = u;
            u = v;
            v = temp;
        }
        for (int k = logs[tree.length]; k >= 0; k--) {
            int nextU = up[k][u];
            if (tree[nextU].depth >= tree[v].depth) {
                u = nextU;
            }
        }
        if (u == v) {
            return new int[]{u, u, u};
        }
        for (int k = logs[tree.length]; k >= 0; k--) {
            int nextU = up[k][u];
            int nextV = up[k][v];
            if (nextU != nextV) {
                u = nextU;
                v = nextV;
            }
        }
        return new int[]{u, tree[u].parent, v};
    }

    public static int getLevelAncestor(int u, int level) {
        int depth = tree[u].depth - level;
        for (int k = logs[tree.length]; k >= 0; k--) {
            int nextU = up[k][u];
            if (tree[nextU].depth >= depth) {
                u = nextU;
            }
        }
        return u;
    }

    public static int distance(int u, int v, int LCA) {
        return tree[u].depth + tree[v].depth - 2 * tree[LCA].depth;
    }

    public static int solve(int u, int v) {
        if (u == v) {
            return tree.length;
        }
        int[] LCA = getLCA(u, v);
        if (distance(u, v, LCA[1]) % 2 == 1) {
            return 0;
        }
        if (distance(u, LCA[1], LCA[1]) == distance(v, LCA[1], LCA[1])) {
            return tree.length - tree[LCA[0]].size - tree[LCA[2]].size;
        }
        if (tree[u].depth < tree[v].depth) {
            int temp = u;
            u = v;
            v = temp;
        }
        int uFarParent = getLevelAncestor(u, distance(u, v, LCA[1]) / 2 - 1);
        return tree[tree[uFarParent].parent].size - tree[uFarParent].size;
    }


    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(reader.readLine());
        tree = new Node[n];
        for (int i = 0; i < n; i++) {
            tree[i] = new Node();
        }
        for (int i = 0; i < n - 1; i++) {
            String[] line = reader.readLine().split(" ");
            int a = Integer.parseInt(line[0]) - 1;
            int b = Integer.parseInt(line[1]) - 1;
            tree[a].neighbours.add(b);
            tree[b].neighbours.add(a);
        }
        tree[0].parent = 0;
        dfs(0, 0);
        calculateLogs(n);
        calculateBinaryLifts();
        int m = Integer.parseInt(reader.readLine());
        for (int i = 0; i < m; i++) {
            String[] line = reader.readLine().split(" ");
            int b = Integer.parseInt(line[0]) - 1;
            int esc = Integer.parseInt(line[1]) - 1;
            System.out.println(solve(b, esc));
        }
    }

    public static class Node {
        int size, depth, parent;
        List<Integer> neighbours;

        Node() {
            size = 1;
            depth = 0;
            parent = -1;
            neighbours = new ArrayList<>();
        }
    }
}
