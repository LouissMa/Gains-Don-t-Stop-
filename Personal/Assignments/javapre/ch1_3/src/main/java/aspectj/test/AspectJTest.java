package aspectj.test;

import aspectj.dao.TestDao;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class AspectJTest {
    public static void main(String[] args) {
        ApplicationContext app = new ClassPathXmlApplicationContext("applicationContext.xml");

        TestDao testDao = (TestDao) app.getBean("testDao");

        System.out.println("------ save ------");
        testDao.save();

        System.out.println("------ modify ------");
        testDao.modify();

        System.out.println("------ delete ------");
        testDao.delete();
    }
}