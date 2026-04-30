package com.lab.borrow.web.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;

import javax.servlet.http.HttpServletRequest;

@Controller
public class ErrorPageController {
    @GetMapping("/error")
    public String error(@RequestParam(value = "msg", required = false) String msg, HttpServletRequest request) {
        request.setAttribute("message", msg == null ? "系统错误" : msg);
        request.setAttribute("path", request.getRequestURI());
        return "error";
    }
}
