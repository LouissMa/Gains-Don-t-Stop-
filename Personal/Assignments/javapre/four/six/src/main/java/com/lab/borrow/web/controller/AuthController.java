package com.lab.borrow.web.controller;

import com.lab.borrow.domain.Const;
import com.lab.borrow.entity.User;
import com.lab.borrow.service.UserService;
import com.lab.borrow.web.dto.UserLoginForm;
import com.lab.borrow.web.dto.UserRegisterForm;
import org.springframework.stereotype.Controller;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;

import javax.annotation.Resource;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;
import javax.validation.Valid;

@Controller
@RequestMapping("/auth")
public class AuthController {
    @Resource
    private UserService userService;

    @GetMapping("/login")
    public String loginPage(HttpServletRequest request) {
        request.setAttribute("form", new UserLoginForm());
        return "login";
    }

    @PostMapping("/login")
    public String login(@Valid UserLoginForm form, BindingResult bindingResult, HttpSession session, HttpServletRequest request) {
        if (bindingResult.hasErrors()) {
            request.setAttribute("message", bindingResult.getFieldError() == null ? "参数错误" : bindingResult.getFieldError().getDefaultMessage());
            request.setAttribute("form", form);
            return "login";
        }

        User user = userService.login(form.getUsername(), form.getPassword());
        session.setAttribute(Const.SESSION_USER, user);
        return Const.ROLE_ADMIN.equals(user.getRole()) ? "redirect:/" : "redirect:/devices";
    }

    @GetMapping("/register")
    public String registerPage(HttpServletRequest request) {
        request.setAttribute("form", new UserRegisterForm());
        return "register";
    }

    @PostMapping("/register")
    public String register(@Valid UserRegisterForm form, BindingResult bindingResult, HttpSession session, HttpServletRequest request) {
        if (bindingResult.hasErrors()) {
            request.setAttribute("message", bindingResult.getFieldError() == null ? "参数错误" : bindingResult.getFieldError().getDefaultMessage());
            request.setAttribute("form", form);
            return "register";
        }

        User user = userService.register(form.getUsername(), form.getPassword(), form.getRealName(), form.getStudentNo(), form.getPhone(), form.getEmail());
        session.setAttribute(Const.SESSION_USER, user);
        return "redirect:/devices";
    }

    @GetMapping("/logout")
    public String logout(HttpSession session) {
        session.invalidate();
        return "redirect:/auth/login";
    }
}
