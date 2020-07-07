package top.sodagreen.java.experiment.ex1;

/**
 * @author acooz
 */
public class SaddlePoint {

    public static void main(String[] args) {
        int[][] saddleTest = {{1, 2, 3, 4}, {2, 3, 4, 5}, {3, 4, 5, 6}, {6, 7, 8, 9}};
        saddlePoint(saddleTest);
    }

    /**
     * 找出一个二维数组的鞍点，即该位置上的元素在该行上最大，在该列上最小（注：一个二维数组也可能没有这样的鞍点
     * 仅考虑方阵情况
     */
    public static void saddlePoint(int[][] arr) {
        int length = arr.length;
        for (int i = 0; i < length; i++) {
            int pos = -1;
            int max = 0;
            for (int j = 0; j < length; j++) {
                if (max < arr[i][j]) {
                    max = arr[i][j];
                    pos = j;
                }
            }
            boolean isExistSaddlePoint = true;
            for (int[] ints : arr) {
                if (ints[pos] < arr[i][pos]) {
                    isExistSaddlePoint = false;
                    break;
                }
            }
            if (isExistSaddlePoint) {
                System.out.println("第" + i + "行鞍点为arr[" + i + "]" + "[" + pos + "]=" + arr[i][pos]);
            } else {
                System.out.println("第" + i + "行不存在鞍点");
            }
        }
    }
}
