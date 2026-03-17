package aspectj.aspect;

import org.aspectj.lang.JoinPoint;
import org.aspectj.lang.ProceedingJoinPoint;
import org.aspectj.lang.annotation.*;
import org.springframework.stereotype.Component;

@Aspect
@Component
public class MyAspect {

    @Pointcut("execution(* aspectj.dao.TestDaoImpl.*(..))")
    public void myPointCut() {
    }

    @Before("myPointCut()")
    public void before(JoinPoint jp) {
        System.out.println("前置通知：权限控制...");
        System.out.println("目标方法：" + jp.getSignature().getName());
    }

    @AfterReturning("myPointCut()")
    public void afterReturning(JoinPoint jp) {
        System.out.println("后置返回通知：" + jp.getSignature().getName());
    }

    @Around("myPointCut()")
    public Object around(ProceedingJoinPoint pjp) throws Throwable {
        System.out.println("环绕开始：开启事务...");
        Object obj = pjp.proceed();
        System.out.println("环绕结束：关闭事务...");
        return obj;
    }

    @AfterThrowing(value = "myPointCut()", throwing = "e")
    public void afterThrowing(Throwable e) {
        System.out.println("异常通知：" + e.getMessage());
    }

    @After("myPointCut()")
    public void after() {
        System.out.println("最终通知：释放资源...");
    }
}