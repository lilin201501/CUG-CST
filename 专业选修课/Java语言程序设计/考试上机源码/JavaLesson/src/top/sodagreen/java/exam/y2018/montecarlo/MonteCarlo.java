package top.sodagreen.java.exam.y2018.montecarlo;

/**
 * @author acooz
 * 使用蒙特卡洛方法计算曲线y=x^2与曲线y=√x围成的一个叶形图的面积。
 */
public class MonteCarlo {
    public static void main(String[] args) {
        MonteCarlo leaf = new MonteCarlo();
        System.out.println(leaf.getArea(0.5, 0, 1, 100)-leaf.getArea(2, 0, 1, 100));
    }

    /**
     * @param coefficient the coefficient of x
     * @return the line area from a to b
     */
    public double getArea(double coefficient, double a, double b, int steps) {
        double stepLen = (b - a) / steps;
        double area = 0;
        for (double i = a; i <= b; i += stepLen) {
            area += Math.pow(i, coefficient);
        }
        return area/steps;
    }
}
