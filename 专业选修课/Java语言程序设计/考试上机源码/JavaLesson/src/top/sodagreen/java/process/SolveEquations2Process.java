package top.sodagreen.java.process;

import java.util.Scanner;

/**
 * @author acooz
 * Solve quadratic equations
 */
public class SolveEquations2Process {
    public static void main(String[] args) {
        solveEquationsTest();
    }

    /**
     * @param a Quadratic coefficient
     * @param b First-order coefficient
     * @param c Constant term coefficient
     * @return solve Information
     */
    public static String solveEquations(double a, double b, double c) {
        if (a == 0) {
            if (b == 0) {
                if (c == 0) {
                    return "The equation has arbitrary solutions";
                } else {
                    return "input error";
                }
            } else {
                return "x = " + (-c) / b;
            }
        } else {
            double delta = b * b - 4 * a * c;
            double realNum = -b / (2 * a);
            if (delta >= 0) {
                return "x1 = " + (realNum + Math.sqrt(delta) / (2 * a)) + "   x2 = " + (realNum - Math.sqrt(delta) / (2 * a));
            } else {
                delta = Math.abs(delta);
                return "x1 = " + realNum + " + " + Math.sqrt(delta) / (2 * a) + "i   x2 = " + realNum + " - " + Math.sqrt(delta) / (2 * a);
            }
        }
    }

    /**
     * Quadratic coefficient test method
     */
    public static void solveEquationsTest() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("input a, b, c in order");
        double a = scanner.nextDouble();
        double b = scanner.nextDouble();
        double c = scanner.nextDouble();
        System.out.println(solveEquations(a, b, c));
    }

}
