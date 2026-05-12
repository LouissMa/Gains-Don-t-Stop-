package com.lab.borrow.web.controller;

import com.lab.borrow.common.PageResult;
import com.lab.borrow.domain.Const;
import com.lab.borrow.entity.User;
import com.lab.borrow.service.UserService;
import com.lab.borrow.web.dto.AdminUserCreateForm;
import com.lab.borrow.web.dto.AdminUserUpdateForm;
import org.springframework.stereotype.Controller;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;

import javax.annotation.Resource;
import javax.servlet.http.HttpServletRequest;
import javax.validation.Valid;

@Controller
@RequestMapping("/admin/users")
public class AdminUserWebController {
    @Resource
    private UserService userService;

    @GetMapping
    public String list(@RequestParam(value = "keyword", required = false) String keyword,
                       @RequestParam(value = "page", required = false, defaultValue = "1") int page,
                       @RequestParam(value = "size", required = false, defaultValue = "10") int size,
                       HttpServletRequest request) {
        PageResult<User> userPage = userService.pageUsers(keyword, page, size);
        request.setAttribute("userPage", userPage);
        request.setAttribute("keyword", keyword == null ? "" : keyword);
        return "user_list";
    }

    @GetMapping("/new")
    public String newForm(HttpServletRequest request) {
        request.setAttribute("form", new AdminUserCreateForm());
        request.setAttribute("roles", new String[]{Const.ROLE_ADMIN, Const.ROLE_USER});
        request.setAttribute("action", "/admin/users");
        return "user_form";
    }

    @PostMapping
    public String create(@Valid AdminUserCreateForm form, BindingResult bindingResult, HttpServletRequest request) {
        if (bindingResult.hasErrors()) {
            request.setAttribute("message", bindingResult.getFieldError() == null ? "参数错误" : bindingResult.getFieldError().getDefaultMessage());
            request.setAttribute("form", form);
            request.setAttribute("roles", new String[]{Const.ROLE_ADMIN, Const.ROLE_USER});
            request.setAttribute("action", "/admin/users");
            return "user_form";
        }
        userService.createByAdmin(form.getUsername(), form.getPassword(), form.getRealName(), form.getStudentNo(), form.getRole(), form.getPhone(), form.getEmail());
        return "redirect:/admin/users";
    }

    @GetMapping("/{id}/edit")
    public String editForm(@PathVariable("id") Integer id, HttpServletRequest request) {
        User user = userService.getById(id);
        AdminUserUpdateForm form = new AdminUserUpdateForm();
        form.setRealName(user.getRealName());
        form.setStudentNo(user.getStudentNo());
        form.setPhone(user.getPhone());
        form.setEmail(user.getEmail());
        form.setRole(user.getRole());
        request.setAttribute("form", form);
        request.setAttribute("roles", new String[]{Const.ROLE_ADMIN, Const.ROLE_USER});
        request.setAttribute("action", "/admin/users/" + id);
        request.setAttribute("userId", id);
        return "user_edit";
    }

    @PostMapping("/{id}")
    public String update(@PathVariable("id") Integer id, @Valid AdminUserUpdateForm form, BindingResult bindingResult, HttpServletRequest request) {
        if (bindingResult.hasErrors()) {
            request.setAttribute("message", bindingResult.getFieldError() == null ? "参数错误" : bindingResult.getFieldError().getDefaultMessage());
            request.setAttribute("form", form);
            request.setAttribute("roles", new String[]{Const.ROLE_ADMIN, Const.ROLE_USER});
            request.setAttribute("action", "/admin/users/" + id);
            request.setAttribute("userId", id);
            return "user_edit";
        }
        userService.updateByAdmin(id, form.getRealName(), form.getStudentNo(), form.getPhone(), form.getEmail(), form.getRole());
        return "redirect:/admin/users";
    }

    @PostMapping("/{id}/disable")
    public String disable(@PathVariable("id") Integer id) {
        userService.setUserStatus(id, Const.USER_STATUS_INACTIVE);
        return "redirect:/admin/users";
    }

    @PostMapping("/{id}/enable")
    public String enable(@PathVariable("id") Integer id) {
        userService.setUserStatus(id, Const.USER_STATUS_ACTIVE);
        return "redirect:/admin/users";
    }

    @PostMapping("/{id}/delete")
    public String delete(@PathVariable("id") Integer id) {
        userService.deleteUser(id);
        return "redirect:/admin/users";
    }
}
