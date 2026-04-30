package com.lab.borrow.service.impl;

import com.lab.borrow.common.BizException;
import com.lab.borrow.common.PageResult;
import com.lab.borrow.domain.Const;
import com.lab.borrow.entity.User;
import com.lab.borrow.mapper.BorrowApplyMapper;
import com.lab.borrow.mapper.BorrowRecordMapper;
import com.lab.borrow.mapper.UserMapper;
import com.lab.borrow.service.UserService;
import com.lab.borrow.util.PasswordUtils;
import com.lab.borrow.util.ValidationUtils;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import javax.annotation.Resource;
import java.util.Date;
import java.util.List;

@Service
public class UserServiceImpl implements UserService {
    @Resource
    private UserMapper userMapper;

    @Resource
    private BorrowRecordMapper borrowRecordMapper;

    @Resource
    private BorrowApplyMapper borrowApplyMapper;

    @Override
    @Transactional
    public User register(String username, String password, String realName, String studentNo, String phone, String email) {
        ValidationUtils.requireUsernameRule(username);
        ValidationUtils.requirePasswordRule(password);
        ValidationUtils.requireRealNameRule(realName);
        ValidationUtils.requireStudentNoRule(studentNo);
        ValidationUtils.requirePhoneRule(phone);
        ValidationUtils.requireEmailRule(email);

        User existingByUsername = userMapper.selectByUsername(username);
        ValidationUtils.require(existingByUsername == null, "用户名已存在");

        User existingByStudentNo = userMapper.selectByStudentNo(studentNo);
        ValidationUtils.require(existingByStudentNo == null, "学号/工号已存在");

        User user = new User();
        user.setUsername(username);
        user.setPassword(PasswordUtils.md5WithSalt(password));
        user.setRealName(realName);
        user.setStudentNo(studentNo);
        user.setRole(Const.ROLE_USER);
        user.setPhone(phone);
        user.setEmail(email);
        user.setStatus(Const.USER_STATUS_ACTIVE);
        user.setLastLoginTime(null);

        userMapper.insert(user);
        user.setPassword(null);
        return user;
    }

    @Override
    @Transactional
    public User login(String username, String password) {
        ValidationUtils.requireNotBlank(username, "用户名不能为空");
        ValidationUtils.requireNotBlank(password, "密码不能为空");

        User user = userMapper.selectByUsername(username);
        if (user == null) {
            throw new BizException("用户名或密码错误");
        }
        if (!Const.USER_STATUS_ACTIVE.equals(user.getStatus())) {
            throw new BizException("用户已被禁用");
        }
        if (!PasswordUtils.md5WithSalt(password).equalsIgnoreCase(user.getPassword())) {
            throw new BizException("用户名或密码错误");
        }

        Date now = new Date();
        userMapper.updateLastLoginTime(user.getUserId(), now);
        user.setLastLoginTime(now);
        user.setPassword(null);
        return user;
    }

    @Override
    @Transactional
    public User createByAdmin(String username, String password, String realName, String studentNo, String role, String phone, String email) {
        ValidationUtils.requireUsernameRule(username);
        ValidationUtils.requirePasswordRule(password);
        ValidationUtils.requireRealNameRule(realName);
        ValidationUtils.requireStudentNoRule(studentNo);
        ValidationUtils.requirePhoneRule(phone);
        ValidationUtils.requireEmailRule(email);
        ValidationUtils.requireNotBlank(role, "角色不能为空");
        ValidationUtils.require(Const.ROLE_ADMIN.equals(role) || Const.ROLE_USER.equals(role), "角色只能是admin或user");

        User existingByUsername = userMapper.selectByUsername(username);
        ValidationUtils.require(existingByUsername == null, "用户名已存在");

        User existingByStudentNo = userMapper.selectByStudentNo(studentNo);
        ValidationUtils.require(existingByStudentNo == null, "学号/工号已存在");

        User user = new User();
        user.setUsername(username);
        user.setPassword(PasswordUtils.md5WithSalt(password));
        user.setRealName(realName);
        user.setStudentNo(studentNo);
        user.setRole(role);
        user.setPhone(phone);
        user.setEmail(email);
        user.setStatus(Const.USER_STATUS_ACTIVE);
        user.setLastLoginTime(null);

        userMapper.insert(user);
        user.setPassword(null);
        return user;
    }

    @Override
    @Transactional
    public void updateProfile(Integer userId, String realName, String studentNo, String phone, String email) {
        ValidationUtils.require(userId != null, "用户ID不能为空");
        ValidationUtils.requireRealNameRule(realName);
        ValidationUtils.requireStudentNoRule(studentNo);
        ValidationUtils.requirePhoneRule(phone);
        ValidationUtils.requireEmailRule(email);

        User existing = userMapper.selectById(userId);
        ValidationUtils.require(existing != null, "用户不存在");

        User byStudentNo = userMapper.selectByStudentNo(studentNo);
        if (byStudentNo != null && !byStudentNo.getUserId().equals(userId)) {
            throw new BizException("学号/工号已存在");
        }

        User update = new User();
        update.setUserId(userId);
        update.setRealName(realName);
        update.setStudentNo(studentNo);
        update.setPhone(phone);
        update.setEmail(email);
        update.setRole(existing.getRole());
        update.setStatus(existing.getStatus());

        userMapper.updateById(update);
    }

    @Override
    @Transactional
    public void updateByAdmin(Integer userId, String realName, String studentNo, String phone, String email, String role) {
        ValidationUtils.require(userId != null, "用户ID不能为空");
        ValidationUtils.requireRealNameRule(realName);
        ValidationUtils.requireStudentNoRule(studentNo);
        ValidationUtils.requirePhoneRule(phone);
        ValidationUtils.requireEmailRule(email);
        ValidationUtils.requireNotBlank(role, "角色不能为空");
        ValidationUtils.require(Const.ROLE_ADMIN.equals(role) || Const.ROLE_USER.equals(role), "角色只能是admin或user");

        User existing = userMapper.selectById(userId);
        ValidationUtils.require(existing != null, "用户不存在");

        User byStudentNo = userMapper.selectByStudentNo(studentNo);
        if (byStudentNo != null && !byStudentNo.getUserId().equals(userId)) {
            throw new BizException("学号/工号已存在");
        }

        User update = new User();
        update.setUserId(userId);
        update.setRealName(realName);
        update.setStudentNo(studentNo);
        update.setPhone(phone);
        update.setEmail(email);
        update.setRole(role);
        update.setStatus(existing.getStatus());

        userMapper.updateById(update);
    }

    @Override
    @Transactional
    public void changePassword(Integer userId, String oldPassword, String newPassword) {
        ValidationUtils.require(userId != null, "用户ID不能为空");
        ValidationUtils.requireNotBlank(oldPassword, "旧密码不能为空");
        ValidationUtils.requirePasswordRule(newPassword);

        User user = userMapper.selectById(userId);
        ValidationUtils.require(user != null, "用户不存在");

        if (!PasswordUtils.md5WithSalt(oldPassword).equalsIgnoreCase(user.getPassword())) {
            throw new BizException("旧密码不正确");
        }
        if (PasswordUtils.md5WithSalt(newPassword).equalsIgnoreCase(user.getPassword())) {
            throw new BizException("新密码不能与旧密码相同");
        }
        userMapper.updatePassword(userId, PasswordUtils.md5WithSalt(newPassword));
    }

    @Override
    @Transactional
    public void setUserStatus(Integer userId, String status) {
        ValidationUtils.require(userId != null, "用户ID不能为空");
        ValidationUtils.requireNotBlank(status, "用户状态不能为空");
        ValidationUtils.require(Const.USER_STATUS_ACTIVE.equals(status) || Const.USER_STATUS_INACTIVE.equals(status), "用户状态只能是active或inactive");

        User user = userMapper.selectById(userId);
        ValidationUtils.require(user != null, "用户不存在");

        if (Const.USER_STATUS_INACTIVE.equals(status)) {
            long activeBorrowCount = borrowRecordMapper.countActiveByUserId(userId) + borrowApplyMapper.countActiveByUserId(userId);
            ValidationUtils.require(activeBorrowCount == 0, "该用户存在进行中的借用记录，禁止禁用");
        }

        userMapper.updateStatus(userId, status);
    }

    @Override
    @Transactional
    public void deleteUser(Integer userId) {
        ValidationUtils.require(userId != null, "用户ID不能为空");

        User user = userMapper.selectById(userId);
        ValidationUtils.require(user != null, "用户不存在");

        long anyBorrow = borrowRecordMapper.countAnyByUserId(userId) + borrowApplyMapper.countAnyByUserId(userId);
        ValidationUtils.require(anyBorrow == 0, "该用户存在借用记录，禁止删除，只允许禁用");

        userMapper.deleteById(userId);
    }

    @Override
    public User getById(Integer userId) {
        ValidationUtils.require(userId != null, "用户ID不能为空");
        User user = userMapper.selectById(userId);
        ValidationUtils.require(user != null, "用户不存在");
        user.setPassword(null);
        return user;
    }

    @Override
    public PageResult<User> pageUsers(String keyword, int page, int size) {
        int safePage = Math.max(page, 1);
        int safeSize = Math.min(Math.max(size, 1), 50);
        int offset = (safePage - 1) * safeSize;

        long total = userMapper.count(keyword);
        List<User> list = userMapper.page(keyword, offset, safeSize);
        for (User u : list) {
            u.setPassword(null);
        }
        return new PageResult<>(list, total, safePage, safeSize);
    }
}
