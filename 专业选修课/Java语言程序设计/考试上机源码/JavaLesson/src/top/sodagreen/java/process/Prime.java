package top.sodagreen.java.process;

import java.util.Scanner;

/**
 * @author acooz
 * Prime number judgment
 */
public class Prime {

//    public static void main(String[] args) {
//        isPrimeTest(100000);
//    }

    public boolean isPrime(int num) {
        int bound = 2;
        if (num < bound) {
            return false;
        }
        //通过查表加快10000以内的运算
        int[] base = {2, 3, 5, 7, 9, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
        for (int i : base) {
            if (i < num && num % i == 0) {
                return false;
            } else if (i >= num) {
                break;
            }
        }

        //超过界限的采用土法判断
        int sqrtRange = (int) Math.sqrt(num) + 1;
        for (int i = 101; i < sqrtRange; ) {
            if (num % i == 0) {
                return false;
            }
            i += 2;
        }
        return true;
    }

    public void isPrime() {
        Scanner scanner = new Scanner(System.in);
        int num = 1;
        while (num > 0) {
            System.out.println("input num you want to judge");
            num = scanner.nextInt();
            System.out.println(isPrime(num));
        }
    }

    private void isPrimeTest(int range) {
        for (int i = 1; i <= range; i++) {
            if (isPrime(i)) {
                System.out.println(i + " is prime ");
            }

        }
    }
}
