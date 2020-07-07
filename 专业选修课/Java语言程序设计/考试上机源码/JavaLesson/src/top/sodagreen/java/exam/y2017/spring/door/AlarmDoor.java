package top.sodagreen.java.exam.y2017.spring.door;

/**
 * @author acooz
 * 门具有open( )和close( )两个基本功能，警铃具有报警功能alarm( )，有的门只有门，有的只有警铃，有的门带警铃
 * 请用Java面向对象思想设计并实现这一问题
 */
public class AlarmDoor extends AbstractDoor implements Alarm {
    @Override
    public void open() {
        System.out.println("Door open");
    }

    @Override
    public void close() {
        System.out.println("Door close");
    }

    @Override
    public void alarm() {
        System.out.println("Door alarm");
    }
}
