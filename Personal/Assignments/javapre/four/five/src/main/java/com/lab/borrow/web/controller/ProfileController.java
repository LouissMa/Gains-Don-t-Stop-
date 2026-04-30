package com.lab.borrow.web.controller;

import com.lab.borrow.domain.Const;
import com.lab.borrow.entity.User;
import com.lab.borrow.service.UserService;
import com.lab.borrow.web.dto.UserPasswordChangeForm;
import com.lab.borrow.web.dto.UserProfileUpdateForm;
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
@RequestMapping("/profile")
public class ProfileController {
    @Resource
    private UserService userService;

    @GetMapping
    public String profilePage(HttpSession session, HttpServletRequest request) {
        User sessionUser = (User) session.getAttribute(Const.SESSION_USER);
        User user = userService.getById(sessionUser.getUserId());
        request.setAttribute("user", user);
        request.setAttribute("profileForm", toProfileForm(user));
        request.setAttribute("passwordForm", new UserPasswordChangeForm());
        return "profile";
    }

    @PostMapping
    public String updateProfile(@Valid UserProfileUpdateForm form, BindingResult bindingResult, HttpSession session, HttpServletRequest request) {
        if (bindingResult.hasErrors()) {
            request.setAttribute("message", bindingResult.getFieldError() == null ? "参数错误" : bindingResult.getFieldError().getDefaultMessage());
            return profilePage(session, request);
        }

        User sessionUser = (User) session.getAttribute(Const.SESSION_USER);
        userService.updateProfile(sessionUser.getUserId(), form.getRealName(), form.getStudentNo(), form.getPhone(), form.getEmail());
        User updated = userService.getById(sessionUser.getUserId());
        session.setAttribute(Const.SESSION_USER, updated);
        request.setAttribute("success", "保存成功");
        return profilePage(session, request);
    }

    @PostMapping("/password")
    public String changePassword(@Valid UserPasswordChangeForm form, BindingResult bindingResult, HttpSession session, HttpServletRequest request) {
        if (bindingResult.hasErrors()) {
            request.setAttribute("message", bindingResult.getFieldError() == null ? "参数错误" : bindingResult.getFieldError().getDefaultMessage());
            return profilePage(session, request);
        }

        User sessionUser = (User) session.getAttribute(Const.SESSION_USER);
        userService.changePassword(sessionUser.getUserId(), form.getOldPassword(), form.getNewPassword());
        request.setAttribute("success", "密码修改成功");
        return profilePage(session, request);
    }

    private UserProfileUpdateForm toProfileForm(User user) {
        UserProfileUpdateForm form = new UserProfileUpdateForm();
        form.setRealName(user.getRealName());
        form.setStudentNo(user.getStudentNo());
        form.setPhone(user.getPhone());
        form.setEmail(user.getEmail());
        return form;
    }
}
