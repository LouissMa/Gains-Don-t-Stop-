package instance;

import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class TestScope {
    public static void main(String[] args) {
        @SuppressWarnings("resource")
        ApplicationContext appCon =
                new ClassPathXmlApplicationContext("applicationContext.xml");
        BeanClass b1 = (BeanClass) appCon.getBean("scope1");
        System.out.println(b1);
        BeanClass b2 = (BeanClass) appCon.getBean("scope1");
        System.out.println(b2);
        System.out.println("==========");
        BeanClass b3 = (BeanClass) appCon.getBean("scope2");
        System.out.println(b3);
        BeanClass b4 = (BeanClass) appCon.getBean("scope2");
        System.out.println(b4);
    }
}