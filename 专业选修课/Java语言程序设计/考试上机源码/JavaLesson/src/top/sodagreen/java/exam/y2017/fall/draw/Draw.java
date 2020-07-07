package top.sodagreen.java.exam.y2017.fall.draw;

import java.awt.BorderLayout;
import java.awt.Graphics;
import java.awt.Polygon;
import java.awt.Color;

import javax.swing.JFrame;
import javax.swing.JPanel;

/**
 * @author acooz
 * 画出sin x在[0,2π]的图形
 */
public class Draw extends JFrame {

    private JPanel mainPanel;
    private static final int WIDTH = 400;
    private static final int HEIGHT = 300;

    public Draw() {
        setLayout(new BorderLayout());
        add(new DrawSine(), BorderLayout.CENTER);
    }

    public static void main(String[] args) {
        Draw frame = new Draw();
        frame.setSize(WIDTH, HEIGHT);
        frame.setTitle("Draw Sin X");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
    }

    static class DrawSine extends JPanel {
        private static final int WIDTH = 400;
        private static final int HEIGHT = 300;
        private static final int MID_X = WIDTH / 2;
        private static final int MID_Y = HEIGHT / 2;

        double f(double x) {
            return Math.sin(x);
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
                p.addPoint(x + MID_X, MID_Y - (int) (50 * f((x / 100.0) * Math.PI)));
            }

            graphics.setColor(Color.red);
            graphics.drawPolyline(p.xpoints, p.ypoints, p.npoints);

        }
    }
}