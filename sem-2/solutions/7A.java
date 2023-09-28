import java.io.*;
import java.util.*;

public class CavesAndTunnels {
    public static Node[] tree;
    public static List<Integer> dfs;
    public static List<Pair> euler;
    public static Pair[][] sparseTable;
    public static int[] noInEuler;
    public static int[] logs;
    public static int[] noInDFS;
    public static int[] segmentTree;
    public static boolean[] visited;
    public static int Nto2K;

    public static void firstDFS(int v, int depth) {
        visited[v] = true;
        tree[v].depth = depth;
        int heavy = v;
        int maxChildSize = 0;
        for (int n : tree[v].neighbours) {
            if (!visited[n]) {
                tree[n].parent = v;
                firstDFS(n, depth + 1);
                tree[v].size += tree[n].size;
                if (tree[n].size > maxChildSize) {
                    heavy = n;
                    maxChildSize = tree[n].size;
                }
            }
        }
        tree[v].heavy = heavy;
    }

    public static void secondDFS(int v) {
        visited[v] = true;
        dfs.add(v);
        noInDFS[v] = dfs.size() - 1;
        if (isLeaf(v)) {
            return;
        }
        tree[tree[v].heavy].up = tree[v].up;
        secondDFS(tree[v].heavy);
        for (int n : tree[v].neighbours) {
            if (!visited[n]) {
                secondDFS(n);
            }
        }
    }

    public static void thirdDFS(int v, int depth) {
        visited[v] = true;
        inject(v, depth);
        for (int n : tree[v].neighbours) {
            if (!visited[n]) {
                thirdDFS(n, depth + 1);
                inject(v, depth);
            }
        }
    }

    public static void inject(int v, int depth) {
        euler.add(new Pair(v, depth));
        noInEuler[v] = euler.size() - 1;
    }

    public static int findMax(int u, int v) {
        int LCA = getLCA(u, v);
        if (LCA == u || LCA == v) {
            return findMaxIfAncestor(u, v);
        }
        return Math.max(findMaxIfAncestor(u, LCA), findMaxIfAncestor(v, LCA));
    }

    public static int findMaxIfAncestor(int u, int v) {
        if (tree[u].depth < tree[v].depth) {
            int temp = u;
            u = v;
            v = temp;
        }
        int answer = Integer.MIN_VALUE;
        while (true) {
            if (tree[tree[u].up].depth > tree[v].depth) {
                answer = Math.max(answer, get(noInDFS[u], noInDFS[tree[u].up]));
                u = tree[tree[u].up].parent;
            } else {
                answer = Math.max(answer, get(noInDFS[u], noInDFS[v]));
                break;
            }
        }
        return answer;
    }

    public static void calculateLogs(int n) {
        logs = new int[n + 1];
        for (int i = 2; i < n + 1; i++) {
            logs[i] = logs[i / 2] + 1;
        }
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

    public static int getLCA(int u, int v) {
        int l = Math.min(noInEuler[u], noInEuler[v]);
        int r = Math.max(noInEuler[u], noInEuler[v]);
        int layer = logs[r - l + 1];
        return (sparseTable[layer][l].depth < sparseTable[layer][r - (1 << layer) + 1].depth) ?
                sparseTable[layer][l].noNode : sparseTable[layer][r - (1 << layer) + 1].noNode;
    }

    public static void combine(int v) {
        segmentTree[v] = Math.max(segmentTree[2 * v + 1], segmentTree[2 * v + 2]);
    }

    public static void add(int v, int value) {
        add(0, 0, Nto2K, v, value);
    }

    public static void add(int v, int l, int r, int qv, int value) {
        if (l + 1 == r) {
            segmentTree[v] += value;
            return;
        }
        int m = l + (r - l) / 2;
        if (qv < m) {
            add(2 * v + 1, l, m, qv, value);
        } else {
            add(2 * v + 2, m, r, qv, value);
        }
        combine(v);
    }

    public static int get(int l, int r) {
        int left = Math.min(l, r);
        int right = Math.max(l, r);
        return get(0, 0, Nto2K, left, right + 1);
    }

    public static int get(int v, int l, int r, int ql, int qr) {
        if (r <= ql || qr <= l) {
            return Integer.MIN_VALUE;
        }
        if (ql <= l && r <= qr) {
            return segmentTree[v];
        }
        int m = l + (r - l) / 2;
        return Math.max(get(2 * v + 1, l, m, ql, qr), get(2 * v + 2, m, r, ql, qr));
    }

    public static void reset() {
        Arrays.fill(visited, false);
    }

    public static boolean isLeaf(int v) {
        return v == 0 ? tree.length == 1 : tree[v].neighbours.size() == 1;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(reader.readLine());
        tree = new Node[n];
        for (int i = 0; i < n; i++) {
            tree[i] = new Node(i);
        }
        for (int i = 0; i < n - 1; i++) {
            String[] line = reader.readLine().split(" ");
            int a = Integer.parseInt(line[0]) - 1;
            int b = Integer.parseInt(line[1]) - 1;
            tree[a].neighbours.add(b);
            tree[b].neighbours.add(a);
        }
        tree[0].parent = 0;

        dfs = new ArrayList<>();
        euler = new ArrayList<>();
        noInEuler = new int[n];
        noInDFS = new int[n];
        visited = new boolean[n];

        firstDFS(0, 0);
        reset();

        secondDFS(0);
        reset();

        thirdDFS(0, 0);

        calculateLogs(euler.size());
        createSparseTable(euler);

        Nto2K = 1 << to2k(dfs.size());
        segmentTree = new int[2 * Nto2K - 1];

        int m = Integer.parseInt(reader.readLine());
        for (int i = 0; i < m; i++) {
            String[] line = reader.readLine().split(" ");
            char command = line[0].charAt(0);
            int a = Integer.parseInt(line[1]) - 1;
            int b = Integer.parseInt(line[2]);
            if (command == 'I') {
                add(noInDFS[a], b);
            } else {
                System.out.println(findMax(a, b - 1));
            }
        }
    }

    public static class Node {
        int size, depth, parent, heavy, up;
        List<Integer> neighbours;

        Node(int i) {
            size = 1;
            depth = 0;
            parent = -1;
            heavy = i;
            up = i;
            neighbours = new ArrayList<>();
        }
    }

    public static class Pair {
        int noNode;
        int depth;

        Pair(int noNode, int depth) {
            this.noNode = noNode;
            this.depth = depth;
        }
    }

    public static int to2k(int x) {
        int a = 1;
        int pow = 0;
        while (true) {
            if (a >= x) {
                return pow;
            }
            a *= 2;
            pow++;
        }
    }
}
