import java.io.*;

public class SimpleStack {
    public static int[] st;
    public static int size;

    public static String push(int n) {
        st[size] = n;
        size++;
        return "ok";
    }

    public static int pop() {
        int result = st[size - 1];
        size--;
        return result;
    }

    public static int back() {
        return st[size - 1];
    }

    public static int size() {
        return size;
    }

    public static String clear() {
        size = 0;
        return "ok";
    }

    public static String exit() {
        return "bye";
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        st = new int[100];
        size = 0;
        while (true) {
            String line = reader.readLine();
            if (line == null) {
                return;
            }
            String[] lines = line.split(" ");
            if (lines[0].equals("push")) {
                System.out.println(push(Integer.parseInt(lines[1])));
            }
            if (lines[0].equals("pop")) {
                System.out.println(pop());
            }
            if (lines[0].equals("back")) {
                System.out.println(back());
            }
            if (lines[0].equals("size")) {
                System.out.println(size());
            }
            if (lines[0].equals("clear")) {
                System.out.println(clear());
            }
            if (lines[0].equals("exit")) {
                System.out.println(exit());
            }
        }
    }
}
