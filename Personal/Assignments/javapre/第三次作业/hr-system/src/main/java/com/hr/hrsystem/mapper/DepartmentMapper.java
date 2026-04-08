package com.hr.hrsystem.mapper;

import com.hr.hrsystem.entity.Department;

public interface DepartmentMapper {
    Department selectById(Integer deptId);
}
