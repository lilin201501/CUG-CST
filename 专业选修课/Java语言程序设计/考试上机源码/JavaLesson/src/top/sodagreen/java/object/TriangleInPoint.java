package top.sodagreen.java.object;

/**
 * @author acooz
 */
public class TriangleInPoint {
    private Point a;
    private Point b;
    private Point c;

    TriangleInPoint() {
    }

    TriangleInPoint(Point a, Point b, Point c) {

        this.a = a;
        this.b = b;
        this.c = c;
    }

    public void setA(Point a) {
        this.a = a;
    }

    public void setB(Point b) {
        this.b = b;
    }

    public void setC(Point c) {
        this.c = c;
    }

    public boolean isTriangle() {
        return ((c.getY() - b.getY()) / (c.getX() - b.getX())) == ((b.getY() - a.getY()) / (b.getX() - a.getX()));
    }

    private double getEdgeLength(Point point1, Point point2) {
        return Math.sqrt(Math.pow((point1.getY() - point2.getY()), 2) - Math.pow((point1.getX() - point2.getX()), 2));
    }

    public double getPerimeter() {
        if (isTriangle()) {
            double e1 = getEdgeLength(a, b);
            double e2 = getEdgeLength(a, c);
            double e3 = getEdgeLength(b, c);
            return e1 + e2 + e3;
        } else {
            return -1;
        }
    }

    public double getArea() {
        if (isTriangle()) {
            double e1 = getEdgeLength(a, b);
            double e2 = getEdgeLength(a, c);
            double e3 = getEdgeLength(b, c);
            double s = (e1 + e2 + e3) / 2f;
            return Math.sqrt(s * (s - e1) * (s - e2) * (s - e3));
        } else {
            return -1;
        }
    }
}
