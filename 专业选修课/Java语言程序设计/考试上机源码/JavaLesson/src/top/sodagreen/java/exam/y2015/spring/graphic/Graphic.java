package top.sodagreen.java.exam.y2015.spring.graphic;

/**
 * @author acooz
 * 1. 定义一个抽象类Shape2D把计算面积定义成抽象方法，PI为常量，具有计算周长（Perimeter）和面积（Area）方法；
 * 2. 定义一个表示颜色的接口Color，具有SetColor ()和FillCoclor（）方法来设置和填充二维图形的颜色；
 * 3. 利用抽象类Shape2D派生子类Circle(圆类)，Rectangle（长方形）和Triangle（三角形）
 * 说明：定义一个抽象类、一个接口，三个子类即可，不需编写主程序。
 */
public class Graphic {
}

class Circle extends AbstractShape2D implements Color {
    Point center;
    double r;
    String color;

    @Override
    public double getArea() {
        return 0;
    }

    @Override
    public double getPerimeter() {
        return 0;
    }

    @Override
    public void setColor(String color) {

    }

    @Override
    public void fillColor() {

    }
}

class Rectangle extends AbstractShape2D implements Color {
    Point p1, p2, p3, p4;
    double length;
    double width;
    String color;

    @Override
    public double getArea() {
        return 0;
    }

    @Override
    public double getPerimeter() {
        return 0;
    }

    @Override
    public void setColor(String color) {

    }

    @Override
    public void fillColor() {

    }
}

class Triangle extends AbstractShape2D implements Color {
    Point p1, p2, p3;
    String color;

    @Override
    public double getArea() {
        return 0;
    }

    @Override
    public double getPerimeter() {
        return 0;
    }

    @Override
    public void setColor(String color) {

    }

    @Override
    public void fillColor() {

    }
}

class Point {
    double x;
    double y;

    Point() {
        x = 0;
        y = 0;
    }

    Point(double x, double y) {
        this.x = x;
        this.y = y;
    }
}
