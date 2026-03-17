package instance;

public class BeanInstanceFactory {

    public BeanClass createBeanClassInstance() {
        return new BeanClass("使用实例工厂实例化 Bean");
    }

}