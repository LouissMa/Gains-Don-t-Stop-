package instance;

public class BeanStaticFactory {

    public static BeanClass createBeanClassInstance() {
        return new BeanClass("使用静态工厂实例化 Bean");
    }

}