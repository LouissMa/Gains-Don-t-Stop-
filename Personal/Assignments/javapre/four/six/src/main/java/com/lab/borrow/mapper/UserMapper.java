package com.lab.borrow.mapper;

import com.lab.borrow.entity.User;
import org.apache.ibatis.annotations.Param;

import java.util.Date;
import java.util.List;

public interface UserMapper {
    int insert(User user);

    User selectById(@Param("userId") Integer userId);

    User selectByUsername(@Param("username") String username);

    User selectByStudentNo(@Param("studentNo") String studentNo);

    int updateById(User user);

    int updateStatus(@Param("userId") Integer userId, @Param("status") String status);

    int updatePassword(@Param("userId") Integer userId, @Param("password") String password);

    int updateLastLoginTime(@Param("userId") Integer userId, @Param("lastLoginTime") Date lastLoginTime);

    int deleteById(@Param("userId") Integer userId);

    List<User> page(@Param("keyword") String keyword, @Param("offset") int offset, @Param("size") int size);

    long count(@Param("keyword") String keyword);
}
