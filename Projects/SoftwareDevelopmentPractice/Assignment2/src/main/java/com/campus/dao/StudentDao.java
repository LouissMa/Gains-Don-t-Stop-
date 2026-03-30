package com.campus.dao;

import com.campus.entity.Student;
import com.campus.entity.Course;
import org.springframework.stereotype.Repository;

import java.util.*;
import java.util.concurrent.ConcurrentHashMap;

@Repository
public class StudentDao {
    private static final Map<String, Student> students = new ConcurrentHashMap<>();
    private static final Map<String, Course> courses = new LinkedHashMap<>();
    private static final Map<String, Set<String>> studentCourses = new ConcurrentHashMap<>();

    static {
        // Initial courses
        courses.put("C001", new Course("C001", "Java Web开发", "王老师", 4, 50, 0, "周一 1-4节", "教三 301"));
        courses.put("C002", new Course("C002", "Spring MVC实战", "张老师", 2, 30, 0, "周三 5-6节", "实验楼 202"));
        courses.put("C003", new Course("C003", "数据结构与算法", "李老师", 4, 60, 0, "周五 1-4节", "教二 101"));
    }

    public void save(Student student) {
        students.put(student.getStudentId(), student);
    }

    public Student findByStudentId(String studentId) {
        return students.get(studentId);
    }

    public List<Course> findAllCourses() {
        return new ArrayList<>(courses.values());
    }

    public void selectCourse(String studentId, List<String> courseIds) {
        Set<String> selected = studentCourses.getOrDefault(studentId, new HashSet<>());
        for (String cid : courseIds) {
            if (courses.containsKey(cid)) {
                Course course = courses.get(cid);
                if (course.getSelectedCount() < course.getMaxStudents() && !selected.contains(cid)) {
                    selected.add(cid);
                    course.setSelectedCount(course.getSelectedCount() + 1);
                }
            }
        }
        studentCourses.put(studentId, selected);
    }

    public List<Course> findCoursesByStudentId(String studentId) {
        Set<String> cids = studentCourses.getOrDefault(studentId, Collections.emptySet());
        List<Course> result = new ArrayList<>();
        for (String cid : cids) {
            result.add(courses.get(cid));
        }
        return result;
    }
}
