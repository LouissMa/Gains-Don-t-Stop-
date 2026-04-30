package com.lab.borrow.util;

import com.lab.borrow.common.BizException;

import java.util.Date;
import java.util.regex.Pattern;

public final class ValidationUtils {
    private static final Pattern USERNAME_PATTERN = Pattern.compile("^[A-Za-z0-9_]{4,50}$");
    private static final Pattern PHONE_PATTERN = Pattern.compile("^\\d{11}$");
    private static final Pattern EMAIL_PATTERN = Pattern.compile("^[^@\\s]+@[^@\\s]+\\.[^@\\s]+$");

    private ValidationUtils() {
    }

    public static void require(boolean condition, String message) {
        if (!condition) {
            throw new BizException(message);
        }
    }

    public static void requireNotBlank(String value, String message) {
        if (value == null || value.trim().isEmpty()) {
            throw new BizException(message);
        }
    }

    public static void requireLengthBetween(String value, int min, int max, String message) {
        if (value == null) {
            throw new BizException(message);
        }
        int len = value.length();
        if (len < min || len > max) {
            throw new BizException(message);
        }
    }

    public static void requireMaxLength(String value, int max, String message) {
        if (value == null) {
            throw new BizException(message);
        }
        if (value.length() > max) {
            throw new BizException(message);
        }
    }

    public static void requireUsernameRule(String username) {
        requireNotBlank(username, "用户名不能为空");
        require(USERNAME_PATTERN.matcher(username).matches(), "用户名格式不合法，只允许字母、数字、下划线，长度4~50");
    }

    public static void requirePasswordRule(String password) {
        requireNotBlank(password, "密码不能为空");
        requireLengthBetween(password, 6, 20, "密码长度必须为6~20");
    }

    public static void requireRealNameRule(String realName) {
        requireNotBlank(realName, "真实姓名不能为空");
        requireLengthBetween(realName, 2, 50, "真实姓名长度必须为2~50");
    }

    public static void requireStudentNoRule(String studentNo) {
        requireNotBlank(studentNo, "学号/工号不能为空");
        requireMaxLength(studentNo, 20, "学号/工号长度不能超过20");
    }

    public static void requirePhoneRule(String phone) {
        if (phone == null || phone.trim().isEmpty()) {
            return;
        }
        require(PHONE_PATTERN.matcher(phone).matches(), "手机号格式不合法，必须为11位数字");
    }

    public static void requireEmailRule(String email) {
        if (email == null || email.trim().isEmpty()) {
            return;
        }
        require(EMAIL_PATTERN.matcher(email).matches(), "邮箱格式不合法");
    }

    public static void requireNotFuture(Date date, String message) {
        require(date != null, message);
        Date now = new Date();
        require(!date.after(now), message);
    }

    public static void requirePositiveInt(Integer value, String message) {
        require(value != null && value > 0, message);
    }
}
