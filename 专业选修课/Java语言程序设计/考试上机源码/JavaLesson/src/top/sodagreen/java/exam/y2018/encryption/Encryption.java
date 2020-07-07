package top.sodagreen.java.exam.y2018.encryption;

import java.util.Scanner;

/**
 * @author acooz
 * 编程实现基于ASCII码（1个字符转换成2个ASCII值小于32的字符）的加密
 */
public class Encryption {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Encryption enc = new Encryption();

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
