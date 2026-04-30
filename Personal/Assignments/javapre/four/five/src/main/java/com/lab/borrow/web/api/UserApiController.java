package com.lab.borrow.web.api;

import com.lab.borrow.common.PageResult;
import com.lab.borrow.common.Result;
import com.lab.borrow.domain.Const;
import com.lab.borrow.entity.User;
import com.lab.borrow.service.UserService;
import com.lab.borrow.web.dto.AdminUserCreateForm;
import com.lab.borrow.web.dto.AdminUserUpdateForm;
import com.lab.borrow.web.dto.UserPasswordChangeForm;
import com.lab.borrow.web.dto.UserProfileUpdateForm;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import javax.servlet.http.HttpSession;
import javax.validation.Valid;

@RestController
@RequestMapping("/api/users")
public class UserApiController {
    private final UserService userService;

    public UserApiController(UserService userService) {
        this.userService = userService;
    }

    @GetMapping("/page")
    public Result<PageResult<User>> page(@RequestParam(value = "keyword", required = false) String keyword,
                                         @RequestParam(value = "page", required = false, defaultValue = "1") int page,
                                         @RequestParam(value = "size", required = false, defaultValue = "10") int size) {
        return Result.success(userService.pageUsers(keyword, page, size));
    }

    @GetMapping("/{id}")
    public Result<User> get(@PathVariable("id") Integer id) {
        return Result.success(userService.getById(id));
    }

    @PostMapping
    public Result<User> create(@Valid @RequestBody AdminUserCreateForm form, BindingResult bindingResult) {
        if (bindingResult.hasErrors()) {
            return Result.bizFail(bindingResult.getFieldError() == null ? "参数错误" : bindingResult.getFieldError().getDefaultMessage());
        }
        return Result.success(userService.createByAdmin(form.getUsername(), form.getPassword(), form.getRealName(), form.getStudentNo(), form.getRole(), form.getPhone(), form.getEmail()));
    }

    @PostMapping("/{id}")
    public Result<Void> update(@PathVariable("id") Integer id, @Valid @RequestBody AdminUserUpdateForm form, BindingResult bindingResult) {
        if (bindingResult.hasErrors()) {
            return Result.bizFail(bindingResult.getFieldError() == null ? "参数错误" : bindingResult.getFieldError().getDefaultMessage());
        }
        userService.updateByAdmin(id, form.getRealName(), form.getStudentNo(), form.getPhone(), form.getEmail(), form.getRole());
        return Result.success(null);
    }

    @PostMapping("/{id}/enable")
    public Result<Void> enable(@PathVariable("id") Integer id) {
        userService.setUserStatus(id, Const.USER_STATUS_ACTIVE);
        return Result.success(null);
    }

    @PostMapping("/{id}/disable")
    public Result<Void> disable(@PathVariable("id") Integer id) {
        userService.setUserStatus(id, Const.USER_STATUS_INACTIVE);
        return Result.success(null);
    }

    @PostMapping("/{id}/delete")
    public Result<Void> delete(@PathVariable("id") Integer id) {
        userService.deleteUser(id);
        return Result.success(null);
    }

    @PostMapping("/me")
    public Result<Void> updateMe(@Valid @RequestBody UserProfileUpdateForm form, BindingResult bindingResult, HttpSession session) {
        if (bindingResult.hasErrors()) {
            return Result.bizFail(bindingResult.getFieldError() == null ? "参数错误" : bindingResult.getFieldError().getDefaultMessage());
        }
        User me = (User) session.getAttribute(Const.SESSION_USER);
        userService.updateProfile(me.getUserId(), form.getRealName(), form.getStudentNo(), form.getPhone(), form.getEmail());
        session.setAttribute(Const.SESSION_USER, userService.getById(me.getUserId()));
        return Result.success(null);
    }

    @PostMapping("/me/password")
    public Result<Void> changeMyPassword(@Valid @RequestBody UserPasswordChangeForm form, BindingResult bindingResult, HttpSession session) {
        if (bindingResult.hasErrors()) {
            return Result.bizFail(bindingResult.getFieldError() == null ? "参数错误" : bindingResult.getFieldError().getDefaultMessage());
        }
        User me = (User) session.getAttribute(Const.SESSION_USER);
        userService.changePassword(me.getUserId(), form.getOldPassword(), form.getNewPassword());
        return Result.success(null);
    }
}
