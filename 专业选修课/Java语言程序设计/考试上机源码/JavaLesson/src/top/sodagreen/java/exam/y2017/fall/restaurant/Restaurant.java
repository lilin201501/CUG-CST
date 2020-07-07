package top.sodagreen.java.exam.y2017.fall.restaurant;

/**
 * @author acooz
 * 假设一学校新开一家餐厅，餐厅分为包房（VIP restaurant）和大厅(Public restaurant)
 * 客户有教工客户（Teachers）和学生（Students）客户以及校友客户（Alumni）
 * 教工在包房就餐，学生在大厅就餐，校友包房和大厅都可以就餐，编程实现这个功能
 */
public class Restaurant {
    public static void main(String[] args) {
        Student stu = new Student();
        stu.publicRestaurant();
        Teacher tea = new Teacher();
        tea.vipRestaurant();
        Alumni alu = new Alumni();
        alu.publicRestaurant();
        alu.vipRestaurant();
    }

}
