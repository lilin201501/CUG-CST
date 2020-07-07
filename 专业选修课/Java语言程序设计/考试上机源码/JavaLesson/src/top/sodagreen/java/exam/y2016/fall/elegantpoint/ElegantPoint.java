package top.sodagreen.java.exam.y2016.fall.elegantpoint;

import java.util.Scanner;

/**
 * @author acooz
 * 设有一个圆心在坐标原点的圆，已知圆的半径的平方（整数）
 * 设计算法计算圆上的优雅点（圆上的点而且横、纵坐标都是整数的点）的个数。
 */
public class ElegantPoint {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("请输入圆的半径平方：");
        int r2 = scanner.nextInt();
        int r = (int) Math.sqrt(r2);
        int count = 0;
        //扫描每条整数线 x=a （从 x=1 和 x=r）
        for (int x = 1; x <= r; x++) {
            double y = Math.sqrt(r2 - x * x);
            if (y == (double) ((int) y)) {
                count++;
            }
        }
        count = count * 4;
        System.out.println("优雅点个数为： " + count);
    }
}
