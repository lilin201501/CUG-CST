package top.sodagreen.java.process;

import java.util.Scanner;

/**
 * @author acooz
 * Greatest common factor
 * by 更相减损法
 */
public class GreatestCommonFactor {
    public static void main(String[] args) {
        greatestCommonFactorTest();
    }

    public static int greatestCommonFactor(int a, int b) {
        while (a != b) {
            if (a > b) {
                a -= b;
            } else {
                b -= a;
            }
        }
        return a;
    }

    /**
     * Greatest common factor Test
     */
    public static void greatestCommonFactorTest() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("please input two Integers ");
        int a = scanner.nextInt();
        int b = scanner.nextInt();
        System.out.println(greatestCommonFactor(a, b));
    }

}
