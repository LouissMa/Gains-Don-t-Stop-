package com.lab.borrow.web.dto;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.Size;

public class UserProfileUpdateForm {
    @NotBlank
    @Size(min = 2, max = 50)
    private String realName;

    @NotBlank
    @Size(max = 20)
    private String studentNo;

    private String phone;
    private String email;

    public String getRealName() {
        return realName;
    }

    public void setRealName(String realName) {
        this.realName = realName;
    }

    public String getStudentNo() {
        return studentNo;
    }

    public void setStudentNo(String studentNo) {
        this.studentNo = studentNo;
    }

    public String getPhone() {
        return phone;
    }

    public void setPhone(String phone) {
        this.phone = phone;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }
}
