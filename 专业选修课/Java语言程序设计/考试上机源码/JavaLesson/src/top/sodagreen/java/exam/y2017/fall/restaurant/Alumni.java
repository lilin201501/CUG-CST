package top.sodagreen.java.exam.y2017.fall.restaurant;

public class Alumni implements AlumniEating {
    @Override
    public void vipRestaurant() {
        System.out.println("校友可在包房就餐");
    }

    @Override
    public void publicRestaurant() {
        System.out.println("校友也可在大厅就餐");
    }
}
