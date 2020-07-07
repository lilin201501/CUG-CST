package top.sodagreen.java.exam.y2017.spring.bubblesort;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.util.Arrays;

/**
 * @author acooz
 */
public class DrawPadListener implements MouseListener, ActionListener {

    Graphics graphics;

    @Override
    public void actionPerformed(ActionEvent e) {
        int[] num = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
        for (int i = 1; i < num.length; i++) {
            graphics.setColor(Color.WHITE);
            graphics.fillRect(50, 200, 700, 350);
            for (int j = 0; j < num.length - i; j++) {
                if (num[j] > num[j + 1]) {
                    num[j + 1] = (num[j + 1] + num[j]) - (num[j] = num[j + 1]);
                }
            }
            for (int k = 0; k < num.length; k++) {
                graphics.setColor(Color.BLACK);
                graphics.fillRect(100 + 50 * k, 500 - num[k] * 30, 30, num[k] * 30);
                graphics.drawString("" + num[k], 100 + 50 * k, 530);
            }
            System.out.println(Arrays.toString(num));
            try {
                Thread.sleep(500);
            } catch (InterruptedException e1) {
                e1.printStackTrace();
            }
        }
    }

    @Override
    public void mouseClicked(MouseEvent e) {

    }


    @Override
    public void mousePressed(MouseEvent e) {

    }

    @Override
    public void mouseReleased(MouseEvent e) {

    }

    @Override
    public void mouseEntered(MouseEvent e) {

    }


    @Override
    public void mouseExited(MouseEvent e) {

    }

}