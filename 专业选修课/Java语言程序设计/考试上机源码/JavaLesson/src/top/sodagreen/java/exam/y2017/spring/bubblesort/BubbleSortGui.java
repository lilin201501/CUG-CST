package top.sodagreen.java.exam.y2017.spring.bubblesort;


import javax.swing.*;
import java.awt.*;

/**
 * @author acooz
 * 编程实现冒泡排序过程的可视化（图形）
 */
public class BubbleSortGui {
    public static void main(String[] args) {
        JFrame frame = new JFrame();
        JButton btn = new JButton("冒泡排序");

        frame.setTitle("冒泡排序可视化");
        frame.setSize(800, 600);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLayout(new FlowLayout());
        frame.setResizable(false);
        frame.setLocationRelativeTo(null);
        frame.add(btn);
        frame.setVisible(true);
        //动作监听器，用于对按钮的响应
        DrawPadListener dl = new DrawPadListener();
        btn.addActionListener(dl);
        dl.graphics = frame.getGraphics();
    }

}
