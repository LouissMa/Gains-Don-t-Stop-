package com.campus.entity;

public class Course {
    private String courseId;       // 课程ID
    private String courseName;     // 课程名称
    private String teacher;        // 教师
    private Integer credits;       // 学分
    private Integer maxStudents;   // 最大选课人数
    private Integer selectedCount; // 已选人数
    private String timeSlot;       // 上课时间
    private String location;       // 上课地点

    public Course() {}

    public Course(String courseId, String courseName, String teacher, Integer credits, Integer maxStudents, Integer selectedCount, String timeSlot, String location) {
        this.courseId = courseId;
        this.courseName = courseName;
        this.teacher = teacher;
        this.credits = credits;
        this.maxStudents = maxStudents;
        this.selectedCount = selectedCount;
        this.timeSlot = timeSlot;
        this.location = location;
    }

    // Getters and Setters
    public String getCourseId() { return courseId; }
    public void setCourseId(String courseId) { this.courseId = courseId; }
    public String getCourseName() { return courseName; }
    public void setCourseName(String courseName) { this.courseName = courseName; }
    public String getTeacher() { return teacher; }
    public void setTeacher(String teacher) { this.teacher = teacher; }
    public Integer getCredits() { return credits; }
    public void setCredits(Integer credits) { this.credits = credits; }
    public Integer getMaxStudents() { return maxStudents; }
    public void setMaxStudents(Integer maxStudents) { this.maxStudents = maxStudents; }
    public Integer getSelectedCount() { return selectedCount; }
    public void setSelectedCount(Integer selectedCount) { this.selectedCount = selectedCount; }
    public String getTimeSlot() { return timeSlot; }
    public void setTimeSlot(String timeSlot) { this.timeSlot = timeSlot; }
    public String getLocation() { return location; }
    public void setLocation(String location) { this.location = location; }
}
