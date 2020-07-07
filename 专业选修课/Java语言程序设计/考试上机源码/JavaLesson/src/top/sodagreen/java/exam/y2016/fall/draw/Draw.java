package top.sodagreen.java.exam.y2016.fall.draw;

/**
 * @author acooz
 * 用Java程序绘制sin（x）一个周期的图形 略 见y2017.fall.draw
 * 用Java程序模拟表盘式时钟功能
 */
public class Draw {
    public static void main(String[] args) {
        javax.swing.JFrame win = new javax.swing.JFrame();
        win.setSize(400, 400);
        win.add(new Clock());
        win.setVisible(true);
    }
}
