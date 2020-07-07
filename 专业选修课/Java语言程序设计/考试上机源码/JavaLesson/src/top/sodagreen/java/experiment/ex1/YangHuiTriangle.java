package top.sodagreen.java.experiment.ex1;

/**
 * @author acooz
 */
public class YangHuiTriangle {
    public static void main(String[] args) {
        System.out.println("杨辉三角前十行");
        int[][] arrYangHui = yangHuiTriangle(10);
        PrintArray.printArr2(arrYangHui);
    }

    /**
     * 编程输出杨辉三角的前10行
     */
    public static int[][] yangHuiTriangle(int numberOfOutputLines) {
        int[][] arr;
        //创建第一维
        arr = new int[numberOfOutputLines][];
        arr[0] = new int[1];
        arr[0][0] = 1;
        int numInLine = 2;
        //创建第二维
        for (int i = 1; i < numberOfOutputLines; i++) {
            arr[i] = new int[numInLine++];
            arr[i][0] = 1;
            arr[i][arr[i].length - 1] = 1;
            for (int j = 1; j < arr[i].length - 1; j++) {
                arr[i][j] = arr[i - 1][j - 1] + arr[i - 1][j];
                ;
            }
        }
        return arr;
    }
}
