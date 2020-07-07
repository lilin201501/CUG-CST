package top.sodagreen.java.process;

/**
 * @author acooz
 * Find daffodil number
 */
public class DaffodilNumber {
    public static void main(String[] args) {
        daffodilNumber();
    }

    public static void daffodilNumber() {
        int start = 100;
        int end = 1000;
        for (int i = start; i < end; i++) {
            int hundred = i / 100;
            int ten = (i % 100) / 10;
            int one = i % 10;
            int sum = (int) (Math.pow(hundred, 3) + Math.pow(ten, 3) + Math.pow(one, 3));
            if (sum == i) {
                System.out.println(i);
            }
        }
    }
}

