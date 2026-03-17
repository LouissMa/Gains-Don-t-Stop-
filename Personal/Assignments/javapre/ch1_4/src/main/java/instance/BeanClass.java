package instance;

public class BeanClass {

    public String message;

    public BeanClass() {
        message = "通过构造方法实例化 Bean";
    }

    public BeanClass(String message) {
        this.message = message;
    }
}