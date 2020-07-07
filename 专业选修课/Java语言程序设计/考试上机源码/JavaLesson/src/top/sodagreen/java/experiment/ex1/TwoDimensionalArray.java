package top.sodagreen.java.experiment.ex1;

import java.util.Random;

/**
 * @author acooz
 */
public class TwoDimensionalArray {
    public static void main(String[] args) {
        System.out.println("随机生成二维数组");
        int[][] arr = generateRandomArray(10, 10, 100);
        PrintArray.printArr2(arr);
        System.out.println("二维数组中每行最大值");
        PrintArray.printArr1(maxInEachRow(arr));
        System.out.println("二维数组中每列平均值");
        PrintArray.printArr1(averageInEachColumn(arr));
    }

    /**
     * 生成二维随机数组
     */
    public static int[][] generateRandomArray(int row, int column, int bound) {
        int[][] arr;
        Random r = new Random();
        //创建第一维
        arr = new int[row][];
        //创建第二维
        for (int i = 0; i < row; i++) {
            arr[i] = new int[column];
            for (int j = 0; j < column; j++) {
                arr[i][j] = r.nextInt(bound);
                ;
            }
        }
        return arr;
    }

    /**
     * 求出二维随机数组中每行的最大值
     */
    public static int[] maxInEachRow(int[][] arr) {
        int[] maxInEachRow = new int[arr.length];
        for (int i = 0; i < arr.length; i++) {
            int max = 0;
            for (int num : arr[i]) {
                if (max < num) {
                    max = num;
                }
            }
            maxInEachRow[i] = max;
        }
        return maxInEachRow;
    }

    /**
     * 求出二维随机数组中每列的平均值(仅考虑方阵情况
     */
    public static float[] averageInEachColumn(int[][] arr) {
        int length = arr.length;
        float[] averageInEachColumn = new float[length];
        for (int i = 0; i < length; i++) {
            float sum = 0;
            for (int[] ints : arr) {
                sum += ints[i];
            }
            averageInEachColumn[i] = sum / length;
        }
        return averageInEachColumn;
    }
}
