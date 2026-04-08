package com.hr.hrsystem.mapper;

import com.hr.hrsystem.entity.SalaryHistory;

import java.util.List;

public interface SalaryHistoryMapper {
    List<SalaryHistory> selectByEmpIdOrderByDateDesc(Integer empId);
}
