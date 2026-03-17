package service;

import org.springframework.context.support.ClassPathXmlApplicationContext;

public class TestInitAndDestroy {
    public static void main(String[] args) {
        // 为了方便演示销毁方法的执行，这里使用ClassPathXmlApplicationContext
        ClassPathXmlApplicationContext appCon =
                new ClassPathXmlApplicationContext("applicationContext.xml");
        System.out.println("获得对象前");
        MyService life = (MyService) appCon.getBean("beanLife");
        System.out.println("获得对象后" + life);
        appCon.close(); // 关闭容器，销毁Bean对象
    }
}
