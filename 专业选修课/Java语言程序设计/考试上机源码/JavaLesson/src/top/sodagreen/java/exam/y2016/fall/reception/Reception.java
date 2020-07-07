package top.sodagreen.java.exam.y2016.fall.reception;

/**
 * @author acooz
 * 假设一个学校接待方面的程序，招待不同身份的人的食、宿问题
 * 人的身份有：学生、家长和教工
 * 吃的地方有：学生食堂、教工食堂和招待所
 * 住宿的地方有：学生宿舍、教工公寓和招待所
 * 编程实现学校的接待功能
 */
public class Reception {
    public static void main(String[] args) {
        Student stu = new Student();
        stu.eat();
        stu.sleep();
        Teacher tea = new Teacher();
        tea.eat();
        tea.sleep();
        Parents par = new Parents();
        par.eat();
        par.sleep();
    }
}

class Student implements Person {
    @Override
    public void eat() {
        System.out.println("学生去食堂吃饭！");
    }

    @Override
    public void sleep() {
        System.out.println("学生回寝室睡觉！");
    }
}

class Teacher implements Person {
    @Override
    public void eat() {
        System.out.println("教师去教工餐厅吃饭！");
    }

    @Override
    public void sleep() {
        System.out.println("教师回学校公寓睡觉！");
    }
}

class Parents implements Person {
    @Override
    public void eat() {
        System.out.println("家长去招待所饭馆吃饭！");
    }

    @Override
    public void sleep() {
        System.out.println("家长回招待所睡觉！");
    }
}