package com.campus.controller;

import com.campus.entity.Course;
import com.campus.entity.Student;
import com.campus.service.StudentService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;

import java.util.*;

@Controller
@RequestMapping("/student")
public class StudentController {

    @Autowired
    private StudentService studentService;

    @GetMapping("/toRegister")
    public String toRegister(Model model) {
        model.addAttribute("student", new Student());
        prepareFormItems(model);
        return "student/register";
    }

    @PostMapping("/register")
    public String register(@ModelAttribute Student student, Model model, javax.servlet.http.HttpSession session) {
        student.setRegisterTime(new Date());
        studentService.register(student);
        session.setAttribute("currentUser", student);
        model.addAttribute("student", student);
        return "student/profile";
    }

    @GetMapping("/login")
    public String toLogin() {
        return "student/login";
    }

    @PostMapping("/login")
    public String login(@RequestParam String studentId, @RequestParam String password, javax.servlet.http.HttpSession session, Model model) {
        Student student = studentService.findByStudentId(studentId);
        if (student != null && student.getPassword().equals(password)) {
            session.setAttribute("currentUser", student);
            return "redirect:/index.jsp";
        }
        model.addAttribute("error", "学号或密码错误");
        return "student/login";
    }

    @GetMapping("/logout")
    public String logout(javax.servlet.http.HttpSession session) {
        session.invalidate();
        return "redirect:/index.jsp";
    }

    @GetMapping("/profile/{studentId}")
    public String profile(@PathVariable String studentId, Model model) {
        Student student = studentService.findByStudentId(studentId);
        model.addAttribute("student", student);
        return "student/profile";
    }

    @GetMapping("/edit/{studentId}")
    public String edit(@PathVariable String studentId, Model model) {
        Student student = studentService.findByStudentId(studentId);
        model.addAttribute("student", student);
        prepareFormItems(model);
        return "student/edit";
    }

    @PostMapping("/update")
    public String update(@ModelAttribute Student student, Model model) {
        studentService.update(student);
        model.addAttribute("student", student);
        return "redirect:/student/profile/" + student.getStudentId();
    }

    @GetMapping("/courses")
    public String courses(Model model) {
        List<Course> courseList = studentService.findAllCourses();
        model.addAttribute("courseList", courseList);
        // Wrapper for selection
        model.addAttribute("courseSelection", new CourseSelection());
        return "student/courseSelect";
    }

    @PostMapping("/selectCourse")
    public String selectCourse(@ModelAttribute("courseSelection") CourseSelection selection) {
        studentService.selectCourse(selection.getStudentId(), selection.getCourseIds());
        return "redirect:/student/myCourses?studentId=" + selection.getStudentId();
    }

    @GetMapping("/myCourses")
    public String myCourses(@RequestParam String studentId, Model model) {
        List<Course> myCourses = studentService.findMyCourses(studentId);
        model.addAttribute("courseList", myCourses);
        model.addAttribute("studentId", studentId);
        return "student/myCourses";
    }

    private void prepareFormItems(Model model) {
        Map<String, String> genderItems = new LinkedHashMap<>();
        genderItems.put("男", "男");
        genderItems.put("女", "女");
        model.addAttribute("genderItems", genderItems);

        List<String> majorItems = Arrays.asList("计算机科学与技术", "软件工程", "网络工程", "信息安全", "数据科学与大数据技术");
        model.addAttribute("majorItems", majorItems);

        Map<String, String> gradeItems = new LinkedHashMap<>();
        gradeItems.put("大一", "大一");
        gradeItems.put("大二", "大二");
        gradeItems.put("大三", "大三");
        gradeItems.put("大四", "大四");
        model.addAttribute("gradeItems", gradeItems);

        List<String> hobbyItems = Arrays.asList("游戏", "运动", "音乐", "追剧", "学习", "社交");
        model.addAttribute("hobbyItems", hobbyItems);
    }

    // Helper class for course selection form
    public static class CourseSelection {
        private String studentId;
        private List<String> courseIds;

        public String getStudentId() { return studentId; }
        public void setStudentId(String studentId) { this.studentId = studentId; }
        public List<String> getCourseIds() { return courseIds; }
        public void setCourseIds(List<String> courseIds) { this.courseIds = courseIds; }
    }
}
