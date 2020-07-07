package top.sodagreen.java.exam.y2016.spring.drawtriangle;

/**
 * @author acooz
 * 算法设计：在平面内，画任意三条直线，如构成三角形，则删除三角形以外的射线部分，如图1所示。
 * 1. 找出可行的算法并用流程图表示。
 * 2. 定义相应的类、类的成员变量和成员函数（不需要编写主程序）
 */
public class DrawTriangle {
    // >> TODO 因为题目本身没有让写代码， 所以这里也只写一下自己的思路，根本不是因为懒

    /**
     * 可行的算法：
     * 按纯数学角度理解
     * 根据三条直线的起始点画求出斜率
     * 若存在两条直线斜率相等，则很明显构不成三角形
     * 若三条直线斜率均不相等，则能构成三角形
     * 求出直线两两相交的点
     * 根据三角形的三个顶点对三角形进行重绘
     */

    public void drawTriangle(Line line1, Line line2, Line line3) {
        // 判断斜率是否相等
        if (line1.slope() == line2.slope() || line2.slope() == line3.slope() || line1.slope() == line3.slope()) {
            System.out.println("not a triangle");
        } else {
            Point p1 = line1.intersectPoint(line2);
            Point p2 = line1.intersectPoint(line3);
            Point p3 = line2.intersectPoint(line3);

            drawTriangle(p1, p2, p3);
        }
    }

    public void drawTriangle(Point p1, Point p2, Point p3) {
        //......
    }

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

    /**
     * 求该直线与另一条直线的相交点
     *
     * @param line 另一条直线
     * @return 相交点
     */
    Point intersectPoint(Line line) {
        //......
        return new Point();
    }
    //......
}

class Point {
    double x;
    double y;
    //......
}
