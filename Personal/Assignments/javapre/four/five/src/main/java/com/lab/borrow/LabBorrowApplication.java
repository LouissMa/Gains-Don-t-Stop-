package com.lab.borrow;

import com.lab.borrow.domain.Const;
import com.lab.borrow.entity.User;
import com.lab.borrow.mapper.UserMapper;
import com.lab.borrow.util.PasswordUtils;
import org.mybatis.spring.annotation.MapperScan;
import org.springframework.boot.ApplicationRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.builder.SpringApplicationBuilder;
import org.springframework.boot.web.servlet.support.SpringBootServletInitializer;
import org.springframework.context.annotation.Bean;

@SpringBootApplication
@MapperScan("com.lab.borrow.mapper")
public class LabBorrowApplication extends SpringBootServletInitializer {
    public static void main(String[] args) {
        SpringApplication.run(LabBorrowApplication.class, args);
    }

    @Bean
    public ApplicationRunner initDefaultAdmin(UserMapper userMapper) {
        return args -> {
            String desiredPasswordHash = PasswordUtils.md5WithSalt("123456");
            User admin = userMapper.selectByUsername("admin");
            if (admin == null) {
                String studentNo = "A0000001";
                if (userMapper.selectByStudentNo(studentNo) != null) {
                    for (int i = 2; i <= 99; i++) {
                        String candidate = "A0000001_" + i;
                        if (userMapper.selectByStudentNo(candidate) == null) {
                            studentNo = candidate;
                            break;
                        }
                    }
                }
                if (userMapper.selectByStudentNo(studentNo) != null) {
                    studentNo = "A" + (System.currentTimeMillis() % 1000000000L);
                }

                User user = new User();
                user.setUsername("admin");
                user.setPassword(desiredPasswordHash);
                user.setRealName("管理员");
                user.setStudentNo(studentNo);
                user.setRole(Const.ROLE_ADMIN);
                user.setPhone(null);
                user.setEmail(null);
                user.setStatus(Const.USER_STATUS_ACTIVE);
                user.setLastLoginTime(null);
                userMapper.insert(user);
                return;
            }

            String oldDefaultHash = PasswordUtils.md5WithSalt("admin123");
            String currentHash = admin.getPassword() == null ? "" : admin.getPassword().trim();
            if (currentHash.isEmpty() || currentHash.equalsIgnoreCase(oldDefaultHash)) {
                userMapper.updatePassword(admin.getUserId(), desiredPasswordHash);
            }
        };
    }

    @Override
    protected SpringApplicationBuilder configure(SpringApplicationBuilder application) {
        return application.sources(LabBorrowApplication.class);
    }
}
