package top.sodagreen.java.exam.y2017.fall.restaurant;

/**
 * @author acooz
 * 学生
 */
public class Student implements StudentEating {
    @Override
    public void publicRestaurant() {
        System.out.println("学生在大厅就餐");
    }
}
