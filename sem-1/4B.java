import java.io.*;

public class SimpleQueue {
    public static int[] q;
    public static int size;
    public static int head;
    public static int tail;

    public static String push(int n) {
        q[tail % 100] = n;
        tail = (tail + 1) % 100;
        size++;
        return "ok";
    }

    public static int pop() {
        int result = q[head % 100];
        head = (head + 1) % 100;
        size--;
        return result;
    }

    public static int front() {
        return q[head % 100];
    }

    public static int size() {
        return size;
    }

    public static String clear() {
        size = 0;
        head = 0;
        tail = 0;
        return "ok";
    }

    public static String exit() {
        return "bye";
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        q = new int[100];
        size = 0;
        head = 0;
        tail = 0;
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
            if (lines[0].equals("front")) {
                System.out.println(front());
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
