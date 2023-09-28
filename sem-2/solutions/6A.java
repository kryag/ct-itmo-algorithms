import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

public class LCA {
    public static Vertex[] tree;
    public static List<Pair> euler;
    public static int[] noInEuler;
    public static Pair[][] sparseTable;
    public static int[] logs;

    public static void dfs(Vertex v, int depth) {
        add(v, depth);
        for (Vertex child : v.children) {
            dfs(child, depth + 1);
            add(v, depth);
        }
    }

    public static void add(Vertex v, int depth) {
        euler.add(new Pair(v.no, depth));
        noInEuler[v.no] = euler.size() - 1;
    }

    public static void createSparseTable(List<Pair> a) {
        sparseTable = new Pair[logs[a.size()] + 1][a.size()];
        for (int i = 0; i < a.size(); i++) {
            sparseTable[0][i] = a.get(i);
        }
        for (int i = 1; i < sparseTable.length; i++) {
            for (int j = 0; j < a.size(); j++) {
                sparseTable[i][j] = sparseTable[i - 1][j];
                if (j + (1 << (i - 1)) < a.size() && sparseTable[i][j].depth > sparseTable[i - 1][j + (1 << (i - 1))].depth) {
                    sparseTable[i][j] = sparseTable[i - 1][j + (1 << (i - 1))];
                }
            }
        }
    }

    public static void calculateLogs(int n) {
        logs = new int[n + 1];
        logs[1] = 0;
        for (int i = 2; i < n + 1; i++) {
            logs[i] = logs[i / 2] + 1;
        }
    }

    public static int getMinimum(int l, int r) {
        int layer = logs[r - l + 1];
        return (sparseTable[layer][l].depth < sparseTable[layer][r - (1 << layer) + 1].depth) ?
                sparseTable[layer][l].noVertex : sparseTable[layer][r - (1 << layer) + 1].noVertex;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int n, m, p,firstPos, secondPos, curAnswer = 0;
        long x, y, z, result = 0;

        String[] line = reader.readLine().split(" ");
        n = Integer.parseInt(line[0]);
        m = Integer.parseInt(line[1]);

        tree = new Vertex[n];
        euler = new ArrayList<>();
        noInEuler = new int[n];

        for (int i = 0; i < n; i++) {
            tree[i] = new Vertex(i);
        }
        tree[0].setParent(tree[0]);

        line = reader.readLine().split(" ");
        for (int i = 0; i < n - 1; i++) {
            p = Integer.parseInt(line[i]);
            tree[i + 1].setParent(tree[p]);
            tree[p].addChildren(tree[i + 1]);
        }

        dfs(tree[0], 0);

        calculateLogs(euler.size());
        createSparseTable(euler);

        long[] a = new long[2 * m + 1];
        line = reader.readLine().split(" ");
        a[1] = Long.parseLong(line[0]);
        a[2] = Long.parseLong(line[1]);

        line = reader.readLine().split(" ");
        x = Long.parseLong(line[0]);
        y = Long.parseLong(line[1]);
        z = Long.parseLong(line[2]);

        for (int i = 3; i <= 2 * m; i++) {
            a[i] = (x * a[i - 2] + y * a[i - 1] + z) % n;
        }

        for (int i = 1; i <= m; i++) {
            firstPos = noInEuler[(int) ((a[2 * i - 1] + curAnswer) % n)];
            secondPos = noInEuler[(int) a[2 * i]];
            curAnswer = (firstPos < secondPos) ? getMinimum(firstPos, secondPos) : getMinimum(secondPos, firstPos);
            result += curAnswer;
        }

        System.out.println(result);
    }

    public static class Vertex {
        int no;
        Vertex p;
        List<Vertex> children;

        Vertex(int noVertex) {
            no = noVertex;
            p = null;
            children = new ArrayList<>();
        }

        void setParent(Vertex parent) {
            p = parent;
        }

        void addChildren(Vertex child) {
            children.add(child);
        }
    }

    public static class Pair {
        int noVertex;
        int depth;

        Pair(int noVertex, int depth) {
            this.noVertex = noVertex;
            this.depth = depth;
        }
    }
}
