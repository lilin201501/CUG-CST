package top.sodagreen.java.experiment.ex2;

/**
 * @author acooz
 * Trapezoid类具有类型double的上底、下底、高、面积属性，具有返回面积的功能
 */

public class Trapezoid implements InterfaceGraphic {
    private double upperBottom;
    private double lowerBottom;
    private double height;

    Trapezoid() {
        this.upperBottom = 0;
        this.lowerBottom = 0;
        this.height = 0;
    }

    Trapezoid(double upperBottom, double lowerBottom, double height) {
        this.upperBottom = upperBottom;
        this.lowerBottom = lowerBottom;
        this.height = height;
    }

    public void setUpperBottom(double upperBottom) {
        this.upperBottom = upperBottom;
    }

    public void setLowerBottom(double lowerBottom) {
        this.lowerBottom = lowerBottom;
    }

    public void setHeight(double height) {
        this.height = height;
    }

    @Override
    public double getArea() {
        return (upperBottom + lowerBottom) * height / 2;
    }

}
