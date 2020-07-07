package top.sodagreen.java.exam.y2016.fall.draw;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.geom.Line2D;
import java.util.Date;

/**
 * @author acooz
 * 用Java程序模拟表盘式时钟功能
 */
public class Clock extends Canvas implements ActionListener {
    Date date;
    javax.swing.Timer secondTime;
    int hour, minute, second;
    Line2D secondLine, minuteLine, hourLine;
    int a, b, c;
    static final int CARRY = 60;
    /**
     * 用来表示秒针端点坐标的数组
     */
    double[] pointSecX = new double[60], pointSecY = new double[60];

    /**
     * 用来表示分针端点坐标的数组
     */
    double[] pointMinX = new double[60], pointMinY = new double[60];

    /**
     * 用来表示时针端点坐标的数组
     */
    double[] pointHourX = new double[60], pointHourY = new double[60];

    Clock() {
        secondTime = new javax.swing.Timer(1000, this);
        //12点秒针位置
        pointSecX[0] = 0;
        pointSecY[0] = -100;
        //12点分针位置
        pointMinX[0] = 0;
        pointMinY[0] = -90;
        //12点时针位置
        pointHourX[0] = 0;
        pointHourY[0] = -70;
        //刻度为6度
        double angle = 6 * Math.PI / 180;
        //计算出各个数组中的坐标
        for (int i = 0; i < 59; i++) {
            pointSecX[i + 1] = pointSecX[i] * Math.cos(angle) - Math.sin(angle) * pointSecY[i];
            pointSecY[i + 1] = pointSecY[i] * Math.cos(angle) + pointSecX[i] * Math.sin(angle);
            pointMinX[i + 1] = pointMinX[i] * Math.cos(angle) - Math.sin(angle) * pointMinY[i];
            pointMinY[i + 1] = pointMinY[i] * Math.cos(angle) + pointMinX[i] * Math.sin(angle);
            pointHourX[i + 1] = pointHourX[i] * Math.cos(angle) - Math.sin(angle) * pointHourY[i];
            pointHourY[i + 1] = pointHourY[i] * Math.cos(angle) + pointHourX[i] * Math.sin(angle);
        }
        //坐标平移
        for (int i = 0; i < CARRY - 1; i++) {
            pointSecX[i] = pointSecX[i] + 120;
            pointSecY[i] = pointSecY[i] + 120;
            pointMinX[i] = pointMinX[i] + 120;
            pointMinY[i] = pointMinY[i] + 120;
            pointHourX[i] = pointHourX[i] + 120;
            pointHourY[i] = pointHourY[i] + 120;
        }
        secondLine = new Line2D.Double(0, 0, 0, 0);
        minuteLine = new Line2D.Double(0, 0, 0, 0);
        hourLine = new Line2D.Double(0, 0, 0, 0);
        //秒针开始计时
        secondTime.start();
    }

    @Override
    public void paint(Graphics g) {
        //绘制表盘上的小刻度和大刻度
        for (int i = 0; i < CARRY; i++) {
            int m = (int) pointSecX[i];
            int n = (int) pointSecY[i];
            if (i % 5 == 0) {
                g.setColor(Color.red);
                g.fillOval(m - 4, n - 4, 8, 8);
            } else {
                g.setColor(Color.blue);
                g.fillOval(m - 2, n - 2, 4, 4);
            }
        }
        //钟表中心的实心圆
        g.fillOval(115, 115, 10, 10);
        Graphics2D graphics2D = (Graphics2D) g;
        graphics2D.setColor(Color.red);
        graphics2D.draw(secondLine);
        BasicStroke bs = new BasicStroke(3f, BasicStroke.CAP_ROUND, BasicStroke.JOIN_MITER);
        graphics2D.setStroke(bs);
        graphics2D.setColor(Color.blue);
        graphics2D.draw(minuteLine);
        bs = new BasicStroke(6f, BasicStroke.CAP_BUTT, BasicStroke.JOIN_MITER);
        graphics2D.setStroke(bs);
        graphics2D.setColor(Color.black);
        graphics2D.draw(hourLine);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == secondTime) {
            date = new Date();
            String s = date.toString();
            hour = Integer.parseInt(s.substring(11, 13));
            minute = Integer.parseInt(s.substring(14, 16));
            //获取时间中的秒
            second = Integer.parseInt(s.substring(17, 19));
            int h = hour % 12;
            //秒针端点的坐标, 分针端点的坐标, 时针端点的坐标
            a = second;
            b = minute;
            c = h * 5 + minute / 12;
            secondLine.setLine(120, 120, (int) pointSecX[a], (int) pointSecY[a]);
            minuteLine.setLine(120, 120, (int) pointMinX[b], (int) pointMinY[b]);
            hourLine.setLine(120, 120, (int) pointHourX[c], (int) pointHourY[c]);
            repaint();
        }
    }
}

