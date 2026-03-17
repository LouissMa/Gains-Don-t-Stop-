package test;

import instance.BeanClass;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class TestInstance {

    public static void main(String[] args) {

        ApplicationContext app =
                new ClassPathXmlApplicationContext("applicationContext.xml");

        BeanClass bean1 = (BeanClass) app.getBean("constructorInstance");
        System.out.println(bean1.message);

        BeanClass bean2 = (BeanClass) app.getBean("staticFactoryInstance");
        System.out.println(bean2.message);

        BeanClass bean3 = (BeanClass) app.getBean("instanceFactoryInstance");
        System.out.println(bean3.message);

    }

}