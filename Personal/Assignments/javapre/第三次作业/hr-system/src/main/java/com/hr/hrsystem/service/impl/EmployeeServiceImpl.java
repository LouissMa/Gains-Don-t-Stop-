package com.hr.hrsystem.service.impl;

import com.hr.hrsystem.dto.EmployeeSearchCriteria;
import com.hr.hrsystem.dto.PagedResult;
import com.hr.hrsystem.entity.Employee;
import com.hr.hrsystem.exception.NotFoundException;
import com.hr.hrsystem.mapper.EmployeeMapper;
import com.hr.hrsystem.service.EmployeeService;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.math.BigDecimal;
import java.util.List;

@Service
public class EmployeeServiceImpl implements EmployeeService {
    private final EmployeeMapper employeeMapper;

    public EmployeeServiceImpl(EmployeeMapper employeeMapper) {
        this.employeeMapper = employeeMapper;
    }

    @Override
    public List<Employee> listAll() {
        return employeeMapper.selectAllWithDeptName();
    }

    @Override
    public Employee getById(Integer empId) {
        Employee employee = employeeMapper.selectById(empId);
        if (employee == null) {
            throw new NotFoundException("员工不存在: empId=" + empId);
        }
        return employee;
    }

    @Override
    @Transactional
    public Integer create(Employee employee) {
        int rows = employeeMapper.insert(employee);
        if (rows != 1 || employee.getEmpId() == null) {
            throw new RuntimeException("新增员工失败");
        }
        return employee.getEmpId();
    }

    @Override
    @Transactional
    public Employee updateSelective(Integer empId, Employee employee) {
        Employee existing = employeeMapper.selectById(empId);
        if (existing == null) {
            throw new NotFoundException("员工不存在: empId=" + empId);
        }

        employee.setEmpId(empId);
        employeeMapper.updateSelective(employee);
        return employeeMapper.selectById(empId);
    }

    @Override
    @Transactional
    public void deleteById(Integer empId) {
        int rows = employeeMapper.deleteById(empId);
        if (rows == 0) {
            throw new NotFoundException("员工不存在，无法删除: empId=" + empId);
        }
    }

    @Override
    public PagedResult<Employee> search(String keyword, Integer deptId, BigDecimal minSalary, BigDecimal maxSalary, int page, int pageSize) {
        int safePage = Math.max(page, 1);
        int safePageSize = Math.max(pageSize, 1);
        int offset = (safePage - 1) * safePageSize;

        EmployeeSearchCriteria criteria = new EmployeeSearchCriteria();
        criteria.setKeyword(keyword);
        criteria.setDeptId(deptId);
        criteria.setMinSalary(minSalary);
        criteria.setMaxSalary(maxSalary);
        criteria.setOffset(offset);
        criteria.setLimit(safePageSize);

        long total = employeeMapper.countByCriteria(criteria);
        int totalPages = (int) ((total + safePageSize - 1) / safePageSize);
        List<Employee> items = employeeMapper.selectByCriteria(criteria);
        return new PagedResult<>(items, total, totalPages, safePage, safePageSize);
    }

    @Override
    public Employee getDetail(Integer empId) {
        Employee employee = employeeMapper.selectDetail(empId);
        if (employee == null) {
            throw new NotFoundException("员工不存在: empId=" + empId);
        }
        return employee;
    }

    @Override
    @Transactional
    public Integer createAndFailForTransactionTest(Employee employee) {
        int rows = employeeMapper.insert(employee);
        if (rows != 1 || employee.getEmpId() == null) {
            throw new RuntimeException("新增员工失败");
        }
        throw new RuntimeException("事务回滚验证：刻意抛出运行时异常");
    }
}
