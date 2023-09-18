import java.io.*;

public class PriorityQ {
    public static int[] a;
    public static int n;
    public static int heap_size;
    public static int index;

    public static int[] extract_max() {
        if (heap_size == 0) {
            return new int[]{-1};
        } else {
            int max = a[0];
            if (heap_size == 1) {
                heap_size--;
                return new int[]{0, max};
            } else {
                a[0] = a[heap_size - 1];
                heap_size--;
                heapify(0);
                return new int[]{index + 1, max};
            }
        }
    }

    public static int insert(int key) {
        if (heap_size == n) {
            return -1;
        }
        a[heap_size] = Integer.MIN_VALUE;
        heap_size++;
        increase_key(heap_size - 1, key);
        return (index + 1);
    }

    public static int remove(int i) {
        int j = i - 1;
        if (j >= heap_size || j < 0) {
            return -1;
        }
        int deleted = a[j];
        int swap = a[heap_size - 1];
        heap_size--;
        increase_key(j, swap);
        return deleted;
    }

    public static void increase_key(int i, int key) {
        if (key < a[i]) {
            a[i] = key;
            heapify(i);
        } else {
            a[i] = key;
            index = i;
            while (i > 0 && a[parent(i)] < a[i]) {
                index = parent(i);
                int temp = a[i];
                a[i] = a[parent(i)];
                a[parent(i)] = temp;
                i = parent(i);
            }
        }
    }

    public static void heapify(int i) {
        index = i;
        int l = left(i);
        int r = right(i);
        int largest = 0;
        if (l < heap_size && a[l] > a[i]) {
            largest = l;
        } else {
            largest = i;
        }
        if (r < heap_size && a[r] > a[largest]) {
            largest = r;
        }
        if (largest != i) {
            int temp = a[i];
            a[i] = a[largest];
            a[largest] = temp;
            heapify(largest);
        }
    }

    public static int parent(int i) {
        return ((i - 1) / 2);
    }

    public static int left(int i) {
        return (2 * i + 1);
    }

    public static int right(int i) {
        return (2 * i + 2);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String[] nm = reader.readLine().split(" ");
        n = Integer.parseInt(nm[0]);
        int m = Integer.parseInt(nm[1]);
        a = new int[n];

        for (int i = 0; i < m; i++) {
            String[] stringLine = reader.readLine().split(" ");
            int[] line = new int[stringLine.length];
            for (int j = 0; j < stringLine.length; j++) {
                line[j] = Integer.parseInt(stringLine[j]);
            }
            if (line[0] == 1) {
                int[] output = extract_max();
                if (output.length == 1) {
                    System.out.println(output[0]);
                } else {
                    System.out.println(output[0] + " " + output[1]);
                }
            }
            if (line[0] == 2) {
                System.out.println(insert(line[1]));
            }
            if (line[0] == 3) {
                System.out.println(remove(line[1]));
            }
        }
        if (heap_size > 0) {
            System.out.print(a[0]);
        }
        for (int i = 1; i < heap_size; i++) {
            System.out.print(" " + a[i]);
        }
    }
}
