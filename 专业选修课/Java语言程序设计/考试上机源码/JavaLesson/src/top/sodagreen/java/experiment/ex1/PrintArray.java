package top.sodagreen.java.experiment.ex1;

import java.util.Arrays;

/**
 * @author acooz
 */
public class PrintArray {
    /**
     * 打印一维数组
     */
    public static void printArr1(int[] arr) {
        System.out.println(Arrays.toString(arr));
    }

    public static void printArr1(float[] arr) {
        System.out.println(Arrays.toString(arr));
    }

    /**
     * 打印二维数组
     */
    public static void printArr2(int[][] arr) {
        for (int[] value : arr) {
            System.out.println(Arrays.toString(value));
        }
    }
}
