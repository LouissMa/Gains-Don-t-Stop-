package com.lab.borrow.web.handler;

import com.lab.borrow.common.BizException;
import org.springframework.web.bind.annotation.ControllerAdvice;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.servlet.ModelAndView;

import javax.servlet.http.HttpServletRequest;

@ControllerAdvice(basePackages = "com.lab.borrow.web.controller")
public class ViewExceptionHandler {
    @ExceptionHandler(BizException.class)
    public ModelAndView handleBiz(HttpServletRequest request, BizException e) {
        ModelAndView mv = new ModelAndView("error");
        mv.addObject("message", e.getMessage());
        mv.addObject("path", request.getRequestURI());
        return mv;
    }

    @ExceptionHandler(Exception.class)
    public ModelAndView handleSys(HttpServletRequest request, Exception e) {
        ModelAndView mv = new ModelAndView("error");
        mv.addObject("message", "系统错误");
        mv.addObject("path", request.getRequestURI());
        return mv;
    }
}
