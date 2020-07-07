package top.sodagreen.java.object;

import java.util.Scanner;

/**
 * @author acooz
 */
public class QuadraticEquation {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        while (true) {
            System.out.println("please input a, b, c in order");
            double a = scanner.nextDouble();
            double b = scanner.nextDouble();
            double c = scanner.nextDouble();
            QuadraticEquation test = new QuadraticEquation(a, b, c);
            test.solute();
        }
    }

    private double a, b, c;
    private double x1, x2;
    private double r;
    private double v;
    private int type = -1;
    private static final int NO_ANSWER = -1;
    private static final int ANY_ANSWER = 0;
    private static final int ONE_ANSWER = 1;
    private static final int REAL_ANSWER = 2;
    private static final int VIRTUAL_ANSWER = -2;
    private static final double ERR = 1E-5;

    QuadraticEquation() {
        this.a = 0;
        this.b = 0;
        this.c = 0;
    }

    QuadraticEquation(double a, double b, double c) {
        this.a = a;
        this.b = b;
        this.c = c;
    }

    public void solute() {
        calculate();
        showResult();
    }

    public void setA(double a) {
        this.a = a;
    }

    public void setB(double b) {
        this.b = b;
    }

    public void setC(double c) {
        this.c = c;
    }


    private double delta() {
        return b * b - 4 * a * c;
    }

    public void calculate() {
        if (a == 0) {
            if (b == 0) {
                if (c == 0) {
                    type = ANY_ANSWER;
                } else {
                    type = NO_ANSWER;
                }
            } else {
                type = ONE_ANSWER;
                x1 = x2 = (-c) / b;
            }
        } else {
            double d = delta();
            if (Math.abs(d) < ERR) {
                type = ONE_ANSWER;
                x2 = x1 = -b / (2 * a);
            } else if (d > 0) {
                type = REAL_ANSWER;
                x1 = (-b + Math.sqrt(d)) / (2 * a);
                x2 = (-b - Math.sqrt(d)) / (2 * a);
            } else {
                type = VIRTUAL_ANSWER;
                r = -b / (2 * a);
                v = Math.sqrt(-d) / (2 * a);
            }
        }

    }

    public void showResult() {

        if (type == REAL_ANSWER) {
            System.out.println("x1 = " + x1 + "\tx2 = " + x2);
        } else if (type == VIRTUAL_ANSWER) {
            System.out.println("x1 = " + r + "+" + v + " i,\t x2 = " + r + "-" + v + " i");
        } else if (type == ONE_ANSWER) {
            System.out.println("x = " + x1);
        } else if (type == ANY_ANSWER) {
            System.out.println("ANY ANSWER BE OK");
        } else {
            System.out.println("Input coefficient error! NO ANSWER");
        }
    }
}
