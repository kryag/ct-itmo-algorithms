import java.io.*;
import java.util.*;

public class Pianiwa {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        ArrayDeque<Integer> player1 = new ArrayDeque<>();
        int countCards1 = 5;
        ArrayDeque<Integer> player2 = new ArrayDeque<>();
        int countCards2 = 5;
        String[] line1 = reader.readLine().split(" ");
        String[] line2 = reader.readLine().split(" ");
        for (int i = 0; i < line1.length; i++) {
            player1.addLast(Integer.parseInt(line1[i]));
            player2.addLast(Integer.parseInt(line2[i]));
        }
        int countRound = 0;
        int temp1;
        int temp2;
        while (true) {
            temp1 = player1.pollFirst();
            countCards1--;
            temp2 = player2.pollFirst();
            countCards2--;
            if ((temp1 == 0 && temp2 == 9) || (temp1 > temp2 && !(temp2 == 0 && temp1 == 9))) {
                player1.addLast(temp1);
                player1.addLast(temp2);
                countCards1 += 2;
            } else {
                player2.addLast(temp1);
                player2.addLast(temp2);
                countCards2 += 2;
            }
            countRound++;
            if (countCards1 == 0) {
                System.out.println("second" + " " + countRound);
                return;
            }
            if (countCards2 == 0) {
                System.out.println("first" + " " + countRound);
                return;
            }
            if (countRound == 1_000_000) {
                System.out.println("botva");
                return;
            }
        }
    }
}
