package com.lab.borrow.web.api;

import com.lab.borrow.common.Result;
import com.lab.borrow.domain.Const;
import com.lab.borrow.entity.User;
import com.lab.borrow.service.UserService;
import com.lab.borrow.web.dto.UserLoginForm;
import com.lab.borrow.web.dto.UserRegisterForm;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import javax.annotation.Resource;
import javax.servlet.http.HttpSession;
import javax.validation.Valid;

@RestController
@RequestMapping("/api/auth")
public class AuthApiController {
    @Resource
    private UserService userService;

    @PostMapping("/login")
    public Result<User> login(@Valid @RequestBody UserLoginForm form, BindingResult bindingResult, HttpSession session) {
        if (bindingResult.hasErrors()) {
            return Result.bizFail(bindingResult.getFieldError() == null ? "参数错误" : bindingResult.getFieldError().getDefaultMessage());
        }
        User user = userService.login(form.getUsername(), form.getPassword());
        session.setAttribute(Const.SESSION_USER, user);
        return Result.success(user);
    }

    @PostMapping("/register")
    public Result<User> register(@Valid @RequestBody UserRegisterForm form, BindingResult bindingResult, HttpSession session) {
        if (bindingResult.hasErrors()) {
            return Result.bizFail(bindingResult.getFieldError() == null ? "参数错误" : bindingResult.getFieldError().getDefaultMessage());
        }
        User user = userService.register(form.getUsername(), form.getPassword(), form.getRealName(), form.getStudentNo(), form.getPhone(), form.getEmail());
        session.setAttribute(Const.SESSION_USER, user);
        return Result.success(user);
    }
}
