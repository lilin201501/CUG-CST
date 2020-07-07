package top.sodagreen.java.exam.y2017.fall.restaurant;

/**
 * @author acooz
 * 教师
 */
public class Teacher implements TeacherEating {
    @Override
    public void vipRestaurant() {
        System.out.println("教师可在包房就餐");
    }
}
