package com.campus.service;

import com.campus.dao.StudentDao;
import com.campus.entity.Course;
import com.campus.entity.Student;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class StudentService {

    @Autowired
    private StudentDao studentDao;

    public void register(Student student) {
        studentDao.save(student);
    }

    public Student findByStudentId(String studentId) {
        return studentDao.findByStudentId(studentId);
    }

    public void update(Student student) {
        studentDao.save(student);
    }

    public List<Course> findAllCourses() {
        return studentDao.findAllCourses();
    }

    public void selectCourse(String studentId, List<String> courseIds) {
        studentDao.selectCourse(studentId, courseIds);
    }

    public List<Course> findMyCourses(String studentId) {
        return studentDao.findCoursesByStudentId(studentId);
    }
}
