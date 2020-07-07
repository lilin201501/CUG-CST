package top.sodagreen.java.experiment.ex2;

import top.sodagreen.java.object.Point;

/**
 * @author acooz
 */
public class Circle extends AbstractGraphics {
    private Point center;
    private double r;
    private static final double PI = Math.PI;

    public static void main(String[] args) {
        Circle circle = new Circle(new Point(1, 2), 3);
        System.out.println(circle.getPerimeter());
        System.out.println(circle.getArea());
    }

    Circle() {
        this.center = new Point();
        this.r = 1;
    }

    Circle(Point center, double r) {
        this.center = center;
        this.r = r;
    }

    public void setCenter(Point center) {
        this.center = center;
    }

    public void setR(double r) {
        this.r = r;
    }

    @Override
    public double getPerimeter() {
        return 2 * PI * r;
    }

    @Override
    public double getArea() {
        return PI * r * r;
    }

}
