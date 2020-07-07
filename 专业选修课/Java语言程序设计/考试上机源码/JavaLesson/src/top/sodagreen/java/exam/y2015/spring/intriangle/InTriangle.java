package top.sodagreen.java.exam.y2015.spring.intriangle;

/**
 * @author acooz
 * 用面向对象的方法判断平面内的一个点是否在三角形的内部
 * 1. 定义相应的类、类的成员变量和成员函数
 * 2. Java编程使用类和对象判断该点与三角形的内外关系
 * 具体可参考：
 * 原文链接：https://blog.csdn.net/u011489043/article/details/78213650
 */
public class InTriangle {
    /**
     * 利用叉乘法进行判断
     *
     * @param point1 三角形顶点1
     * @param point2 三角形顶点2
     * @param point3 三角形顶点3
     * @param p      检测顶点
     * @return 是否在三角形内部
     */
    public static boolean isInTriangle(Point point1, Point point2, Point point3, Point p) {
        int a = 0, b = 0, c = 0;

        Point vectorA = new Point(p.x - point1.x, p.y - point1.y);
        Point vectorB = new Point(p.x - point2.x, p.y - point2.y);
        Point vectorC = new Point(p.x - point3.x, p.y - point3.y);

        //向量叉乘
        a = vectorA.x * vectorB.y - vectorA.y * vectorB.x;
        b = vectorB.x * vectorC.y - vectorB.y * vectorC.x;
        c = vectorC.x * vectorA.y - vectorC.y * vectorA.x;

        return ((a <= 0 && b <= 0 && c <= 0) || (a > 0 && b > 0 && c > 0));
    }
}

class Point {
    int x;
    int y;

    public Point(int x, int y) {
        this.x = x;
        this.y = y;
    }
}


