package top.sodagreen.java.exam.y2020;

/**
 * @author 191181 20181001775 高天翔
 * 运行环境：
 * IntelliJ IDEA ULTIMATE 2020.1
 * openjdk-14.0.1
 * 使用 MyEclipse 和 非 jdk-14 的开发包运行可能会报错！
 * 参考：无
 */

public class TestSecond {
    public static void main(String[] args) {
        Triangle tri = new Triangle(3, 3, 3);
        System.out.println("三角形边长为3，3，3, 填充色设置为: 红色");
        tri.setColor("red");
        System.out.println("周长：" + tri.getPerimeter() + " 面积" + tri.getArea());
        Rectangle rec = new Rectangle(4, 3);
        System.out.println("长方形长为4，宽为3, 填充色设置为: 绿色");
        tri.setColor("green");
        System.out.println("周长：" + rec.getPerimeter() + " 面积" + rec.getArea());
        Circle cir = new Circle(3, 4, 5);
        System.out.println("圆的坐标为3，4，半径为5, 填充色设置为: 蓝色");
        tri.setColor("blue");
        System.out.println("周长：" + cir.getPerimeter() + " 面积" + cir.getArea());
    }
}

abstract class AbstractShape2D {
    static final double PI = 3.14;

    /**
     * return graphic area
     *
     * @return graphic area
     */
    public abstract double getArea();

    /**
     * return graphic perimeter
     *
     * @return graphic perimeter
     */
    public abstract double getPerimeter();

}

interface Color {
    /**
     * set the color of graphic
     *
     * @param color the color of graphic
     */
    void setColor(String color);

    /**
     * fill the color of graphic
     */
    void fillColor();

}

class Triangle extends AbstractShape2D implements Color {
    private double a;
    private double b;
    private double c;
    String color;

    Triangle() {
    }

    Triangle(double a, double b, double c) {
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

    public boolean isTriangle() {
        return a + b > c && a + c > b && b + c > a;
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

    @Override
    public void setColor(String color) {
        this.color = color;
    }

    @Override
    public void fillColor() {
    }
}

class Rectangle extends AbstractShape2D implements Color {
    double length;
    double width;
    String color;

    Rectangle(double length, double width) {
        this.length = length;
        this.width = width;
    }

    @Override
    public double getArea() {
        return length * width;
    }

    @Override
    public double getPerimeter() {
        return (length + width) * 2;
    }

    @Override
    public void setColor(String color) {
        this.color = color;
    }

    @Override
    public void fillColor() {

    }
}

class Circle extends AbstractShape2D implements Color {
    double centerX;
    double centerY;
    double r;
    String color;

    Circle(double centerX, double centerY, double r) {
        this.centerX = centerX;
        this.centerY = centerY;
        this.r = r;
    }

    @Override
    public double getArea() {
        return Math.PI * r * r;
    }

    @Override
    public double getPerimeter() {
        return 2 * Math.PI * r;
    }

    @Override
    public void setColor(String color) {
        this.color = color;
    }

    @Override
    public void fillColor() {
    }
}
