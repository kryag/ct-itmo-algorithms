import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

public class CheapestEdge {
    public static Vertex[] tree;
    public static Vertex[][] up;
    public static int[][] min;
    public static int[] logs;

    public static void dfs(Vertex v, int depth) {
        v.depth = depth;
        for (Vertex child : v.children) {
            dfs(child, depth + 1);
        }
    }

    public static void binaryLifts() {
        up = new Vertex[logs[tree.length] + 1][tree.length];
        min = new int[logs[tree.length] + 1][tree.length];
        for (int v = 1; v < tree.length; v++) {
            up[0][v] = tree[v].parent;
            min[0][v] = tree[v].edge;
        }
        for (int k = 1; k < up.length; k++) {
            for (int v = 1; v < tree.length; v++) {
                up[k][v] = up[k - 1][up[k - 1][v].no];
                min[k][v] = Math.min(min[k - 1][v], min[k - 1][up[k - 1][v].no]);
            }
        }
    }

    public static long getSum(Vertex u, Vertex v) {
        if (u.depth < v.depth) {
            Vertex temp = v;
            v = u;
            u = temp;
        }
        int answer = Integer.MAX_VALUE;
        for (int k = logs[tree.length]; k >= 0; k--) {
            Vertex nextU = up[k][u.no];
            int minU = min[k][u.no];
            if (nextU.depth >= v.depth) {
                u = nextU;
                answer = Math.min(answer, minU);
            }
        }
        if (u.no == v.no) {
            return answer;
        }
        for (int k = logs[tree.length]; k >= 0; k--) {
            Vertex nextU = up[k][u.no];
            Vertex nextV = up[k][v.no];
            int minU = min[k][u.no];
            int minV = min[k][v.no];
            if (nextU.no != nextV.no) {
                u = nextU;
                v = nextV;
                answer = Math.min(answer, Math.min(minU, minV));
            }
        }
        return Math.min(answer, Math.min(u.edge, v.edge));
    }

    public static void calculateLogs(int n) {
        logs = new int[n + 1];
        for (int i = 2; i < n + 1; i++) {
            logs[i] = logs[i / 2] + 1;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(reader.readLine());
        tree = new Vertex[n + 1];
        tree[0] = new Vertex(0);
        for (int i = 1; i <= n; i++) {
            tree[i] = new Vertex(i);
        }
        for (int i = 2; i <= n; i++) {
            String[] line = reader.readLine().split(" ");
            int x = Integer.parseInt(line[0]);
            int y = Integer.parseInt(line[1]);
            tree[i].setParent(tree[x]);
            tree[x].addChild(tree[i]);
            tree[i].setEdgeWeight(y);
        }
        tree[1].setParent(tree[1]);
        tree[1].setEdgeWeight(Integer.MAX_VALUE);
        dfs(tree[1], 0);
        calculateLogs(tree.length);
        binaryLifts();
        int m = Integer.parseInt(reader.readLine());
        for (int i = 0; i < m; i++) {
            String[] line = reader.readLine().split(" ");
            int x = Integer.parseInt(line[0]);
            int y = Integer.parseInt(line[1]);
            System.out.println(getSum(tree[x], tree[y]));
        }
    }

    public static class Vertex {
        int no, edge, depth;
        Vertex parent;
        List<Vertex> children;

        Vertex(int no) {
            this.no = no;
            this.edge = 0;
            this.depth = 0;
            parent = null;
            children = new ArrayList<>();
        }

        void setParent(Vertex parent) {
            this.parent = parent;
        }

        void setEdgeWeight(int weight) {
            this.edge = weight;
        }

        void addChild(Vertex child) {
            children.add(child);
        }
    }
}
