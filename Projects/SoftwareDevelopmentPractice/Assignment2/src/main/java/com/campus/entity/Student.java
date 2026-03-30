package com.campus.entity;

import java.util.Date;
import java.util.List;

public class Student {
    private String studentId;      // 学号（登录账号）
    private String password;       // 密码
    private String name;           // 姓名
    private String nickname;       // 昵称
    private String gender;         // 性别：男/女
    private Integer age;           // 年龄
    private String major;          // 专业
    private String grade;          // 年级：大一/大二/大三/大四
    private List<String> hobbies; // 爱好：游戏/运动/音乐/追剧/学习/其他
    private String introduction;   // 个人简介
    private String avatarUrl;       // 头像URL
    private Date registerTime;     // 注册时间

    // Getters and Setters
    public String getStudentId() { return studentId; }
    public void setStudentId(String studentId) { this.studentId = studentId; }
    public String getPassword() { return password; }
    public void setPassword(String password) { this.password = password; }
    public String getName() { return name; }
    public void setName(String name) { this.name = name; }
    public String getNickname() { return nickname; }
    public void setNickname(String nickname) { this.nickname = nickname; }
    public String getGender() { return gender; }
    public void setGender(String gender) { this.gender = gender; }
    public Integer getAge() { return age; }
    public void setAge(Integer age) { this.age = age; }
    public String getMajor() { return major; }
    public void setMajor(String major) { this.major = major; }
    public String getGrade() { return grade; }
    public void setGrade(String grade) { this.grade = grade; }
    public List<String> getHobbies() { return hobbies; }
    public void setHobbies(List<String> hobbies) { this.hobbies = hobbies; }
    public String getIntroduction() { return introduction; }
    public void setIntroduction(String introduction) { this.introduction = introduction; }
    public String getAvatarUrl() { return avatarUrl; }
    public void setAvatarUrl(String avatarUrl) { this.avatarUrl = avatarUrl; }
    public Date getRegisterTime() { return registerTime; }
    public void setRegisterTime(Date registerTime) { this.registerTime = registerTime; }
}
