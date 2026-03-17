package service;

public class MyService {
    public MyService() {
        System.out.println("执行构造方法");
    }
    public void initService() {
        System.out.println("initMethod");
    }
    public void destroyService() {
        System.out.println("destroyMethod");
    }
}