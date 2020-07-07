package top.sodagreen.java.exam.y2016.spring.intersect;

/**
 * @author acooz
 * 算法设计：在平面内，画任意一条直线和一个三角形，判断直线是否与三角形相交
 * 1. 找出可行的算法并用流程图表示。
 * 2. 定义相应的类、类的成员变量和成员函数（不需要编写主程序）
 */
public class Intersect {
    // >> TODO 因为题目本身没有让写代码， 所以这里也只写一下自己的思路

    /**
     * 可行的算法：
     * 如果按数学角度理解，直线可以无限延伸
     * 那么首先判断直线斜率与三角形三边斜率是否相同
     * 不相同：肯定相交
     * 相同：判断三角形三个顶点在直线的同一边还是不同边
     * 同一边：不相交
     * 不同边：相交
     */
    public boolean isIntersect(Triangle triangle, Line line) {
        return isSlopeEqual() && isSameSide();
    }

    public boolean isSlopeEqual() {
        // >> TODO 判断直线斜率与三角形三边斜率是否相同
        return false;
    }

    public boolean isSameSide() {
        // >> TODO 判断三角形三个顶点在直线的同一边还是不同边
        return false;
    }

}

class Triangle {
    Point a;
    Point b;
    Point c;
    //......
}

class Line {
    Point startPoint;
    Point endPoint;

    double slope() {
        return (endPoint.y - startPoint.y) / (endPoint.x - startPoint.x);
    }

    double slope(Point startPoint, Point endPoint) {
        return (endPoint.y - startPoint.y) / (endPoint.x - startPoint.x);
    }
    //......
}

class Point {
    double x;
    double y;
    //......
}
