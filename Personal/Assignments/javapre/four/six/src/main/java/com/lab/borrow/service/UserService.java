package com.lab.borrow.service;

import com.lab.borrow.common.PageResult;
import com.lab.borrow.entity.User;

public interface UserService {
    User register(String username, String password, String realName, String studentNo, String phone, String email);

    User login(String username, String password);

    User createByAdmin(String username, String password, String realName, String studentNo, String role, String phone, String email);

    void updateProfile(Integer userId, String realName, String studentNo, String phone, String email);

    void updateByAdmin(Integer userId, String realName, String studentNo, String phone, String email, String role);

    void changePassword(Integer userId, String oldPassword, String newPassword);

    void setUserStatus(Integer userId, String status);

    void deleteUser(Integer userId);

    User getById(Integer userId);

    PageResult<User> pageUsers(String keyword, int page, int size);
}
