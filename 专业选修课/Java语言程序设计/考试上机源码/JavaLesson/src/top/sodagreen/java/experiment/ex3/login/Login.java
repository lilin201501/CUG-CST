package top.sodagreen.java.experiment.ex3.login;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.List;

/**
 * @author acooz
 */
public class Login {
    private JButton buttonLogin;
    private JPanel mainPanel;
    private JTextField textAccount;
    private JTextField textPassword;
    private boolean isInit = false;
    private final List<String> accountList = new ArrayList<>();
    private final List<String> passwordList = new ArrayList<>();
    private static final String FILE_NAME = "login.txt";

    public Login() {
        buttonLogin.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String account = textAccount.getText();
                String password = textPassword.getText();
                if (isLogin(account, password)) {
                    JOptionPane.showMessageDialog(null, "登录成功！");
                } else {
                    JOptionPane.showMessageDialog(null, "登录失败！");
                }
            }
        });
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("Login");
        frame.setContentPane(new Login().mainPanel);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.pack();
        frame.setVisible(true);
        frame.setBounds(500, 500, 300, 200);
    }

    public boolean isLogin(String account, String password) {
        if (!isInit) {
            readFile();
        }
        for (int i = 0; i < accountList.size(); i++) {
            if (account.equals(accountList.get(i)) && password.equals(passwordList.get(i))) {
                return true;
            }
        }
        return false;
    }

    public void readFile() {
        isInit = true;
        File sourceFile = new File("." + File.separator + FILE_NAME);
        try (
                FileInputStream fis = new FileInputStream(sourceFile);
                InputStreamReader isr = new InputStreamReader(fis, StandardCharsets.UTF_8);
                BufferedReader reader = new BufferedReader(isr);
        ) {
            String line = null;
            while ((line = reader.readLine()) != null) {
                String[] lineSplit = line.split(" ");
                accountList.add(lineSplit[0]);
                passwordList.add(lineSplit[1]);
            }
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

}
