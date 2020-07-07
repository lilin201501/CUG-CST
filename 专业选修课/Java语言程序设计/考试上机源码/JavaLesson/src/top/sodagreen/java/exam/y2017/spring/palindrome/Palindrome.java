package top.sodagreen.java.exam.y2017.spring.palindrome;

import java.util.Scanner;

/**
 * @author acooz
 * 输入一个字符串，求出其中最长的回文串。
 * 子串的含义是：在原串中连续出现的字符串片段。
 * 回文的含义是：正着看和倒着看相同，如abba和yyxyy
 * 在判断时，应忽略所有标点符号和空格，且忽略大小写，但输出保持原样（在回文串的首部和尾部不要输出多余字符）
 * 输入字符串长度不超过5000，且占据单独一行。应输出最长的回文串，如果有多个，输出起始位置最靠左的
 */
public class Palindrome {
    private int lo, maxLen;
    private static final int MIN_LEN = 2;
    private static final int MAX_LEN = 5000;

    public static void main(String[] args) {
        Palindrome p = new Palindrome();
        System.out.println("please input text");
        String text = "";
        Scanner scanner = new Scanner(System.in);
        text = scanner.nextLine();
        System.out.println(p.longestPalindrome(text));
    }

    public String longestPalindrome(String s) {
        int len = s.length();
        if (len < MIN_LEN || len > MAX_LEN) {
            return "";
        }

        for (int i = 0; i < len - 1; i++) {
            //assume odd length, try to extend Palindrome as possible
            extendPalindrome(s, i, i);
            //assume even length.
            extendPalindrome(s, i, i + 1);
        }
        return s.substring(lo, lo + maxLen);
    }

    private void extendPalindrome(String s, int j, int k) {
        while (j >= 0 && k < s.length() && s.charAt(j) == s.charAt(k)) {
            j--;
            k++;
        }
        if (maxLen < k - j - 1) {
            lo = j + 1;
            maxLen = k - j - 1;
        }
    }
}