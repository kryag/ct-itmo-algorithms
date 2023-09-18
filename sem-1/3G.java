import java.io.*;

public class AmongThem {
    public static long n;
    public static long m;

    public static boolean winImpostors() {
        return ((n * n + n) / 2) >= m;
    }

    public static boolean possibleRounds(long count) {
        return (n * count - ((count * (count - 1)) / 2)) >= m;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(reader.readLine());
        for (int i = 0; i < t; i++) {
            String[] line = reader.readLine().split(" ");
            n = Long.parseLong(line[0]);
            m = Long.parseLong(line[1]);
            if (!winImpostors()) {
                System.out.println("Crewmates");
                System.out.println(n);
            } else {
                long result = 0;
                long l = 1;
                long r = n;
                while (r - l > 100) {
                    long med = (l + r) / 2;
                    if (possibleRounds(med)) {
                        result = med;
                        r = med;
                    } else {
                        l = med;
                    }
                }
                for (long j = l; j <= r; j++) {
                    if (possibleRounds(j)) {
                        result = j;
                        break;
                    }
                }
                System.out.println("Impostors");
                System.out.println(result);
            }
        }
    }
}
