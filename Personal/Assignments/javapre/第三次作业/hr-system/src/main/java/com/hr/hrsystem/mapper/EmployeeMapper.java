package com.hr.hrsystem.mapper;

import com.hr.hrsystem.dto.EmployeeSearchCriteria;
import com.hr.hrsystem.entity.Employee;

import java.util.List;

public interface EmployeeMapper {
    List<Employee> selectAllWithDeptName();

    Employee selectById(Integer empId);

    int insert(Employee employee);

    int updateSelective(Employee employee);

    int deleteById(Integer empId);

    long countByCriteria(EmployeeSearchCriteria criteria);

    List<Employee> selectByCriteria(EmployeeSearchCriteria criteria);

    Employee selectDetail(Integer empId);
}
