package top.sodagreen.java.exam.y2020;

import java.util.Scanner;

/**
 * @author 191181 20181001775 高天翔
 * 运行环境：
 * IntelliJ IDEA ULTIMATE 2020.1
 * openjdk-14.0.1
 * 使用 MyEclipse 和 非 jdk-14 的开发包运行可能会报错！
 * 参考：无
 */

// >> TODO 算法的缺点：
// >> TODO 算法仅能对ASCII码表上的字母数字和符号进行加解密，对中文加解密不友好
// >> TODO 改进措施：
// >> TODO 可以使用Unicode编码，使用正则表达式转换为10进制编码后，再进行加解密操作

public class TestFirst {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        TestFirst enc = new TestFirst();

        System.out.println("please input text you want to encrypt");
        String text = scanner.nextLine();
        System.out.println("the text after encrypt: ");
        System.out.println(enc.encrypt(text));

        System.out.println("please input text you want to decrypt");
        String decryptText = scanner.nextLine();
        System.out.println("the text after decrypt: ");
        System.out.println(enc.decrypt(decryptText));
    }

    public String encrypt(String text) {
        StringBuilder encryptText = new StringBuilder();
        for (int i = 0; i < text.length(); i++) {
            int charNum = text.charAt(i);
            encryptText.append((char) ((charNum) / 32)).append((char) ((charNum) % 32));
        }
        return encryptText.toString();
    }

    public String decrypt(String text) {
        int isFormRight = 2;
        if (text.length() % isFormRight != 0) {
            return "";
        }
        StringBuilder decryptText = new StringBuilder();
        for (int i = 0; i < text.length(); ) {
            int char1 = text.charAt(i++);
            int char2 = text.charAt(i++);

            decryptText.append((char) ((char1 * 32 + char2)));
        }
        return decryptText.toString();
    }

}