import java.io.*;

public class BuildSortNet {

    public static void comparatorType1(int i) {
        StringBuilder s = new StringBuilder();
        if (i % 2 == 1) {
            i--;
        }
        s.append(i / 2);
        s.append(" ");
        for (int j = 1; j < i; j += 2) {
            s.append(j);
            s.append(" ");
            s.append(j + 1);
            s.append(" ");
        }
        s.setLength(s.length() - 1);
        System.out.println(s);
    }
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(reader.readLine());
        switch (n) {
            case 1 -> System.out.println("1 0 0");
            case 2 -> {
                System.out.println("2 1 1");
                comparatorType1(2);
            }
            case 3 -> {
                System.out.println("3 3 3");
                comparatorType1(2);
                System.out.println("1 2 3");
                comparatorType1(2);
            }
            case 4 -> {
                System.out.println("4 6 3");
                comparatorType1(4);
                System.out.println("2 1 4 2 3");
                comparatorType1(4);
            }
            case 5 -> {
                System.out.println("5 11 6");
                comparatorType1(5);
                System.out.println("2 1 4 2 3");
                comparatorType1(5);
                System.out.println("1 4 5");
                System.out.println("2 1 3 2 4");
                comparatorType1(5);
            }
            case 6 -> {
                System.out.println("6 15 6");
                comparatorType1(6);
                System.out.println("2 1 4 2 3");
                comparatorType1(6);
                System.out.println("2 3 6 4 5");
                System.out.println("2 1 3 2 4");
                comparatorType1(6);
            }
            case 7 -> {
                System.out.println("7 18 6");
                comparatorType1(7);
                System.out.println("3 1 4 2 3 6 7");
                comparatorType1(7);
                System.out.println("3 2 7 3 6 4 5");
                System.out.println("3 1 3 2 4 5 7");
                comparatorType1(7);
            }
            case 8 -> {
                System.out.println("8 24 6");
                comparatorType1(8);
                System.out.println("4 1 4 2 3 5 8 6 7");
                comparatorType1(8);
                System.out.println("4 1 8 2 7 3 6 4 5");
                System.out.println("4 1 3 2 4 5 7 6 8");
                comparatorType1(8);
            }
            case 9 -> {
                System.out.println("9 37 10");
                comparatorType1(9);
                System.out.println("4 1 4 2 3 5 8 6 7");
                comparatorType1(9);
                System.out.println("4 1 8 2 7 3 6 4 5");
                System.out.println("4 1 3 2 4 5 7 6 8");
                comparatorType1(9);
                System.out.println("1 8 9");
                System.out.println("4 1 5 2 6 3 7 4 8");
                System.out.println("4 1 3 2 4 5 7 6 8");
                comparatorType1(9);
            }
            case 10 -> {
                System.out.println("10 42 10");
                comparatorType1(10);
                System.out.println("4 1 4 2 3 5 8 6 7");
                comparatorType1(10);
                System.out.println("4 1 8 2 7 3 6 4 5");
                System.out.println("4 1 3 2 4 5 7 6 8");
                comparatorType1(10);
                System.out.println("2 7 10 8 9");
                System.out.println("4 1 5 2 6 3 7 4 8");
                System.out.println("4 1 3 2 4 5 7 6 8");
                comparatorType1(10);
            }
            case 11 -> {
                System.out.println("11 46 10");
                comparatorType1(11);
                System.out.println("5 1 4 2 3 5 8 6 7 10 11");
                comparatorType1(11);
                System.out.println("4 1 8 2 7 3 6 4 5");
                System.out.println("5 1 3 2 4 5 7 6 8 9 11");
                comparatorType1(11);
                System.out.println("3 6 11 7 10 8 9");
                System.out.println("4 1 5 2 6 3 7 4 8");
                System.out.println("5 1 3 2 4 5 7 6 8 9 11");
                comparatorType1(11);
            }
            case 12 -> {
                System.out.println("12 54 10");
                comparatorType1(12);
                System.out.println("6 1 4 2 3 5 8 6 7 9 12 10 11");
                comparatorType1(12);
                System.out.println("4 1 8 2 7 3 6 4 5");
                System.out.println("6 1 3 2 4 5 7 6 8 9 11 10 12");
                comparatorType1(12);
                System.out.println("4 5 12 6 11 7 10 8 9");
                System.out.println("4 1 5 2 6 3 7 4 8");
                System.out.println("6 1 3 2 4 5 7 6 8 9 11 10 12");
                comparatorType1(12);
            }
            case 13 -> {
                System.out.println("13 57 10");
                comparatorType1(13);
                System.out.println("6 1 4 2 3 5 8 6 7 9 12 10 11");
                comparatorType1(13);
                System.out.println("5 1 8 2 7 3 6 4 5 12 13");
                System.out.println("6 1 3 2 4 5 7 6 8 9 11 10 12");
                comparatorType1(13);
                System.out.println("5 4 13 5 12 6 11 7 10 8 9");
                System.out.println("5 1 5 2 6 3 7 4 8 9 13");
                System.out.println("6 1 3 2 4 5 7 6 8 9 11 10 12");
                comparatorType1(13);
            }
            case 14 -> {
                System.out.println("14 64 10");
                comparatorType1(14);
                System.out.println("6 1 4 2 3 5 8 6 7 9 12 10 11");
                comparatorType1(14);
                System.out.println("6 1 8 2 7 3 6 4 5 11 14 12 13");
                System.out.println("6 1 3 2 4 5 7 6 8 9 11 10 12");
                comparatorType1(14);
                System.out.println("6 3 14 4 13 5 12 6 11 7 10 8 9");
                System.out.println("6 1 5 2 6 3 7 4 8 9 13 10 14");
                System.out.println("6 1 3 2 4 5 7 6 8 9 11 10 12");
                comparatorType1(14);
            }
            case 15 -> {
                System.out.println("15 70 10");
                comparatorType1(15);
                System.out.println("7 1 4 2 3 5 8 6 7 9 12 10 11 14 15");
                comparatorType1(15);
                System.out.println("7 1 8 2 7 3 6 4 5 10 15 11 14 12 13");
                System.out.println("7 1 3 2 4 5 7 6 8 9 11 10 12 13 15");
                comparatorType1(15);
                System.out.println("7 2 15 3 14 4 13 5 12 6 11 7 10 8 9");
                System.out.println("7 1 5 2 6 3 7 4 8 9 13 10 14 11 15");
                System.out.println("7 1 3 2 4 5 7 6 8 9 11 10 12 13 15");
                comparatorType1(15);
            }
            case 16 -> {
                System.out.println("16 80 10");
                comparatorType1(16);
                System.out.println("8 1 4 2 3 5 8 6 7 9 12 10 11 13 16 14 15");
                comparatorType1(16);
                System.out.println("8 1 8 2 7 3 6 4 5 9 16 10 15 11 14 12 13");
                System.out.println("8 1 3 2 4 5 7 6 8 9 11 10 12 13 15 14 16");
                comparatorType1(16);
                System.out.println("8 1 16 2 15 3 14 4 13 5 12 6 11 7 10 8 9");
                System.out.println("8 1 5 2 6 3 7 4 8 9 13 10 14 11 15 12 16");
                System.out.println("8 1 3 2 4 5 7 6 8 9 11 10 12 13 15 14 16");
                comparatorType1(16);
            }
        }
    }
}
