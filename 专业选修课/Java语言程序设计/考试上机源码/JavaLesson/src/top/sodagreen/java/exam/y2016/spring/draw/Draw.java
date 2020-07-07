package top.sodagreen.java.exam.y2016.spring.draw;

import java.awt.BorderLayout;
import java.awt.Graphics;
import java.awt.Polygon;
import java.awt.Color;

import javax.swing.JFrame;
import javax.swing.JPanel;

/**
 * @author acooz
 * 画出5x-e^x 的图形 86
 * 复用画Sinx函数，修改了一些内容
 * 编程绘制正弦曲线一个周期的图形 12 略
 */
public class Draw extends JFrame {

    private JPanel mainPanel;
    private static final int WIDTH = 400;
    private static final int HEIGHT = 300;

    public Draw() {
        setLayout(new BorderLayout());
        add(new DrawEine(), BorderLayout.CENTER);
    }

    public static void main(String[] args) {
        Draw frame = new Draw();
        frame.setSize(WIDTH, HEIGHT);
        frame.setTitle("Draw");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
    }

    static class DrawEine extends JPanel {
        private static final int WIDTH = 400;
        private static final int HEIGHT = 300;
        private static final int MID_X = WIDTH / 2;
        private static final int MID_Y = HEIGHT / 2;

        double f(double x) {
            return 5 * x - Math.pow(Math.E, x);
        }

        @Override
        protected void paintComponent(Graphics graphics) {
            super.paintComponent(graphics);

            //x轴
            graphics.drawLine(0, MID_Y, WIDTH, MID_Y);
            graphics.drawString("x", WIDTH - 20, MID_Y + 20);
            //x轴箭头
            graphics.drawLine(WIDTH, MID_Y, WIDTH - 10, MID_Y - 10);
            graphics.drawLine(WIDTH, MID_Y, WIDTH - 10, MID_Y + 10);
            //y轴
            graphics.drawLine(MID_X, 0, MID_X, HEIGHT);
            graphics.drawString("y", MID_X + 20, 20);
            //y轴箭头
            graphics.drawLine(MID_X, 0, MID_X - 10, 10);
            graphics.drawLine(MID_X, 0, MID_X + 10, 10);


            Polygon p = new Polygon();

            for (int x = -MID_X; x <= MID_X; x++) {
                System.out.println(MID_Y - (int) (f(x)));
                p.addPoint(x + MID_X + 20, MID_Y - (int) (f(x)) - 20);
            }

            graphics.setColor(Color.red);
            graphics.drawPolyline(p.xpoints, p.ypoints, p.npoints);

        }
    }
}