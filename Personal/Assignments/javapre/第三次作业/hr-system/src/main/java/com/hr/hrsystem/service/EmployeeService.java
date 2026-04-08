package com.hr.hrsystem.service;

import com.hr.hrsystem.dto.PagedResult;
import com.hr.hrsystem.entity.Employee;

import java.math.BigDecimal;
import java.util.List;

public interface EmployeeService {
    List<Employee> listAll();

    Employee getById(Integer empId);

    Integer create(Employee employee);

    Employee updateSelective(Integer empId, Employee employee);

    void deleteById(Integer empId);

    PagedResult<Employee> search(String keyword, Integer deptId, BigDecimal minSalary, BigDecimal maxSalary, int page, int pageSize);

    Employee getDetail(Integer empId);

    Integer createAndFailForTransactionTest(Employee employee);
}
