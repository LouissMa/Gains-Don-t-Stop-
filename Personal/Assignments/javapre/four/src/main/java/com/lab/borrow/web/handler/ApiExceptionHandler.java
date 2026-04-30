package com.lab.borrow.web.handler;

import com.lab.borrow.common.BizException;
import com.lab.borrow.common.Result;
import org.springframework.validation.BindException;
import org.springframework.web.bind.MethodArgumentNotValidException;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.RestControllerAdvice;

@RestControllerAdvice(basePackages = "com.lab.borrow.web.api")
public class ApiExceptionHandler {
    @ExceptionHandler(BizException.class)
    public Result<Void> handleBiz(BizException e) {
        return new Result<>(e.getCode(), e.getMessage(), null);
    }

    @ExceptionHandler({MethodArgumentNotValidException.class, BindException.class})
    public Result<Void> handleValid(Exception e) {
        String msg = "参数错误";
        if (e instanceof MethodArgumentNotValidException) {
            MethodArgumentNotValidException ex = (MethodArgumentNotValidException) e;
            if (ex.getBindingResult().hasFieldErrors() && ex.getBindingResult().getFieldError() != null) {
                msg = ex.getBindingResult().getFieldError().getDefaultMessage();
            }
        }
        if (e instanceof BindException) {
            BindException ex = (BindException) e;
            if (ex.getBindingResult().hasFieldErrors() && ex.getBindingResult().getFieldError() != null) {
                msg = ex.getBindingResult().getFieldError().getDefaultMessage();
            }
        }
        return Result.bizFail(msg);
    }

    @ExceptionHandler(Exception.class)
    public Result<Void> handleSys(Exception e) {
        return Result.sysFail("系统错误");
    }
}
