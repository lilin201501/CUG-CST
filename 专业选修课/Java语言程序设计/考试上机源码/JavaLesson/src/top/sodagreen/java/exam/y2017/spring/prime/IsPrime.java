package top.sodagreen.java.exam.y2017.spring.prime;

import top.sodagreen.java.process.Prime;

import java.util.Scanner;

/**
 * @author acooz
 * 从键盘输入n个位于x与y之间的数，输出素数的个数
 * 使用 top.sodagreen.java.process.Prime 中的代码
 */
public class IsPrime {
    public static void main(String[] args) {
        int count = 0;
        Scanner scanner = new Scanner(System.in);
        Prime p = new Prime();
        int num = 1;
        while (num > 0) {
            System.out.println("please input num");
            num = scanner.nextInt();
            if (p.isPrime(num)) {
                count++;
            }
        }
        System.out.println("the numbers of prime is : " + count);
    }
}
