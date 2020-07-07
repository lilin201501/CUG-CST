package top.sodagreen.java.exam.y2015.spring.integral;

/**
 * @author acooz
 * 求由曲线y=x^2, y=2-x^2所围成的平面图形的面积。
 * 修改y2018.montecarlo程序
 * <p>
 * 计算f(x)=1-x^2在0-1区间的面积
 * 1. 找出可行的算法并用流程图表示
 * 2. 用编程语言编程实现
 * 略 与上题类似 略
 */
public class Integral {
    public static void main(String[] args) {
        Integral leaf = new Integral();
        System.out.println(leaf.getAreaF2(0, 1, 100) - leaf.getAreaF1(0, 1, 100));
    }

    /**
     * @return the line area from a to b
     */
    public double getAreaF1(double a, double b, int steps) {
        double stepLen = (b - a) / steps;
        double area = 0;
        for (double i = a; i <= b; i += stepLen) {
            area += Math.pow(i, 2);
        }
        return area / steps;
    }

    public double getAreaF2(double a, double b, int steps) {
        double stepLen = (b - a) / steps;
        double area = 0;
        for (double i = a; i <= b; i += stepLen) {
            area += 2 - Math.pow(i, 2);
        }
        return area / steps;
    }

}
