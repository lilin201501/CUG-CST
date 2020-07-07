package top.sodagreen.java.exam.y2020;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * @author 191181 20181001775 高天翔
 * 运行环境：
 * IntelliJ IDEA ULTIMATE 2020.1
 * openjdk-14.0.1
 * 使用 MyEclipse 和 非 jdk-14 的开发包运行可能会报错！
 * 参考：无
 */

public class TestThird {
    private static final JFrame FRAME = new JFrame("TestThird");
    private JPanel mainPanel;
    private JTextField textFieldA;
    private JTextField textFieldB;
    private JTextField textFieldC;
    private JTextField textFieldResult;
    private JLabel labelR;
    private JLabel labelC;
    private JLabel labelB;
    private JLabel labelA;
    private JButton buttonSolute;
    private JButton buttonExit;

    public TestThird() {
        buttonSolute.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                double a = Double.parseDouble(textFieldA.getText());
                double b = Double.parseDouble(textFieldB.getText());
                double c = Double.parseDouble(textFieldC.getText());
                QuadraticEquation test = new QuadraticEquation(a, b, c);
                test.calculate();
                String result = test.getResult();
                textFieldResult.setText(result);
            }
        });
        buttonExit.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                FRAME.dispose();
            }
        });
    }

    public static void main(String[] args) {

        FRAME.setContentPane(new TestThird().mainPanel);
        FRAME.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        FRAME.pack();
        FRAME.setVisible(true);
        FRAME.setBounds(500, 500, 1000, 500);
    }
}

class QuadraticEquation {
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

    public String getResult() {
        if (type == REAL_ANSWER) {
            return "x1 = " + String.format("%.4f", x1) + "   x2 = " + String.format("%.4f", x2);
        } else if (type == VIRTUAL_ANSWER) {
            return " x1 = " + String.format("%.4f", r) + "+" + String.format("%.4f", v) + " i,   x2 = " + String.format("%.4f", r) + "-" + String.format("%.4f", v) + " i";
        } else if (type == ONE_ANSWER) {
            return "x = " + String.format("%.4f", x1);
        } else if (type == ANY_ANSWER) {
            return "ANY ANSWER BE OK";
        } else {
            return "Input coefficient error! NO ANSWER";
        }
    }
}
