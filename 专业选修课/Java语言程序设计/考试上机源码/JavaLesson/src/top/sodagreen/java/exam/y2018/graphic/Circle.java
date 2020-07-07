package top.sodagreen.java.exam.y2018.graphic;

/**
 * @author acooz
 * 用抽象类和接口计算带填充色的二维图形的周长和面积
 * 以圆为例
 */
public class Circle extends AbstractShape implements GraphicColor {
    private double centerX;
    private double centerY;
    private String color;
    private double r;
    private static final double PI = Math.PI;

    public static void main(String[] args) {
        Circle circle = new Circle(1, 2, 3);
        System.out.println(circle.getPerimeter());
        System.out.println(circle.getArea());
    }

    Circle() {
        this.centerX = 0;
        this.centerY = 0;
        this.r = 1;
    }

    Circle(double centerX, double centerY, double r) {
        this.centerX = centerX;
        this.centerY = centerY;
        this.r = r;
    }

    public void setCenter(double centerX, double centerY) {
        this.centerX = centerX;
        this.centerY = centerY;
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

    @Override
    public void setColor(String color) {
        this.color = color;
    }

    @Override
    public String getColor() {
        return color;
    }
}
