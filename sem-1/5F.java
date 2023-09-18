import java.io.*;

public class LNS {
    public static int[] dp;
    public static int upperBound(int x) {
        int l = -1;
        int r = dp.length;
        while (l + 1 < r) {
            int m = (l + r) / 2;
            if (dp[m] <= x) {
                l = m;
            }
            else {
                r = m;
            }
        }
        return l + 1;
    }

    public static void main(String[] args) throws IOException {
        Scanner scanner = new Scanner(System.in);
        int n = 0;
        if (scanner.hasNextLine()) {
            n = Integer.parseInt(scanner.nextLine());
        }
        int[] temp = new int[n];
        int count = 0;
        while (scanner.hasNextLine()) {
            Scanner scannerLine = new Scanner(scanner.nextLine());
            while (scannerLine.hasNextInt()) {
                temp[count] = scannerLine.nextInt();
                count++;
            }
        }
        scanner.close();
        int[] a = new int[n + 1];
        for (int i = 0; i < n; i++) {
            a[i + 1] = temp[n - 1 - i];
        }
        dp = new int[n + 1];
        int[] last = new int[n + 1];
        int[] prev = new int[n + 1];
        for (int i = 0; i <= n; i++) {
            dp[i] = Integer.MAX_VALUE;
            last[i] = -1;
            prev[i] = -1;
        }
        dp[0] = Integer.MIN_VALUE;
        for (int i = 1; i < n + 1; i++) {
            int j = upperBound(a[i]);
            dp[j] = a[i];
            last[j] = i;
            prev[i] = last[j - 1];
        }
        int ans = 0;
        for (int i = n; i > 0; i--) {
            if (dp[i] != Integer.MAX_VALUE) {
                ans = i;
                System.out.println(i);
                break;
            }
        }
        ans = last[ans];
        StringBuilder result = new StringBuilder();
        while (ans != -1) {
            result.append(n - (ans - 1));
            result.append(" ");
            ans = prev[ans];
        }
        result.setLength(result.length() - 1);
        System.out.println(result);
    }
}

class Scanner {

    private final int BUFFER_SIZE = 1024;
    private final Reader reader;
    private final char[] buffer = new char[BUFFER_SIZE];
    private int countCharInBuffer;
    private int pos;
    private int nextInt;
    private String nextLine;
    private String nextWord;
    private final String lineSeparator = System.lineSeparator();

    public Scanner(String line) throws IOException {
        this.reader = new StringReader(line);
        readIntoBuffer();
    }

    public Scanner(InputStream s) throws IOException {
        this.reader = new InputStreamReader(s);
        readIntoBuffer();
    }

    public Scanner(String file, String encoding) throws IOException, FileNotFoundException,
            UnsupportedEncodingException {
        this.reader = new InputStreamReader(new FileInputStream(file), encoding);
    }

    private void readIntoBuffer() throws IOException{
        countCharInBuffer = reader.read(buffer);
        pos = 0;
    }

    public boolean hasNextLine() throws IOException {
        StringBuilder sb = new StringBuilder();
        if (pos == countCharInBuffer) {
            readIntoBuffer();
        }
        if (countCharInBuffer > 0) {
            while (true) {
                sb.append(buffer[pos]);
                pos++;
                if (sb.length() >= lineSeparator.length()) {
                    boolean hasSep = true;
                    for (int i = 0; i < lineSeparator.length(); i++) {
                        if (sb.charAt(sb.length() - 1 - i) != lineSeparator.charAt(lineSeparator.length() - 1 - i)){
                            hasSep = false;
                            break;
                        }
                    }
                    if (hasSep) {
                        break;
                    }
                }
                if (pos == countCharInBuffer) {
                    readIntoBuffer();
                    if (countCharInBuffer <= 0) {
                        if (sb.length() > 0) {
                            nextLine = sb.toString();
                            return true;
                        } else {
                            return false;
                        }
                    }
                }
            }
            sb.setLength(sb.length() - lineSeparator.length());
            if (sb.length() == 0) {
                nextLine = "";
            } else {
                nextLine = sb.toString();
            }
            return true;
        } else {
            return false;
        }
    }

    public String nextLine() {
        return nextLine;
    }

    public boolean hasNextInt() throws IOException {
        StringBuilder sb = new StringBuilder();
        if (pos >= countCharInBuffer) {
            readIntoBuffer();
        }
        if (countCharInBuffer > 0) {
            while (true) {
                if (Character.isDigit(buffer[pos]) || (buffer[pos] == '-')) {
                    sb.append(buffer[pos]);
                    pos++;
                } else {
                    if (sb.length() > 0) {
                        nextInt = Integer.parseInt(sb.toString());
                        pos++;
                        return true;
                    } else {
                        pos++;
                    }
                }
                if (pos == countCharInBuffer) {
                    readIntoBuffer();
                    if (countCharInBuffer <= 0) {
                        if (sb.length() == 0) {
                            return false;
                        } else {
                            nextInt = Integer.parseInt(sb.toString());
                            return true;
                        }
                    }
                }
            }
        } else {
            return false;
        }
    }

    public int nextInt() {
        return nextInt;
    }


    public void close() throws IOException {
        reader.close();
    }
}
