package top.sodagreen.java.experiment.ex2;

/**
 * @author acooz
 * Trangle类具有类型为double的三个边，以及周长、面积属性
 * Trangle类具有返回周长、面积以及修改三个边的功能
 * 以及一个boolean型的属性，该属性用来判断三个属能否构成一个三角形。
 */
public class Triangle extends AbstractGraphics {
    private double a;
    private double b;
    private double c;
    private boolean isTriangle = false;

    Triangle() {
    }

    Triangle(double a, double b, double c) {
        this.a = a;
        this.b = b;
        this.c = c;
        checkIsTriangle();
    }

    public void setA(double a) {
        this.a = a;
        checkIsTriangle();
    }

    public void setB(double b) {
        this.b = b;
        checkIsTriangle();
    }

    public void setC(double c) {
        this.c = c;
        checkIsTriangle();
    }

    public boolean isTriangle() {
        return isTriangle;
    }

    private void checkIsTriangle() {
        isTriangle = a + b > c && a + c > b && b + c > a;
    }

    @Override
    public double getPerimeter() {
        if (isTriangle()) {
            return a + b + c;
        } else {
            return -1;
        }
    }

    @Override
    public double getArea() {
        if (isTriangle()) {
            double s = (a + b + c) / 2f;
            return Math.sqrt(s * (s - a) * (s - b) * (s - c));
        } else {
            return -1;
        }
    }
}
