package com.hr.hrsystem.controller;

import com.hr.hrsystem.dto.EmployeeDetailLazyResponse;
import com.hr.hrsystem.dto.IdResponse;
import com.hr.hrsystem.dto.PagedResult;
import com.hr.hrsystem.entity.Employee;
import com.hr.hrsystem.service.EmployeeService;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.math.BigDecimal;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

@RestController
@RequestMapping("/api/employees")
public class EmployeeController {
    private final EmployeeService employeeService;

    public EmployeeController(EmployeeService employeeService) {
        this.employeeService = employeeService;
    }

    @GetMapping
    public List<Employee> listAll() {
        return employeeService.listAll();
    }

    @GetMapping("/{id}")
    public Employee getById(@PathVariable("id") Integer id) {
        return employeeService.getById(id);
    }

    @PostMapping
    public ResponseEntity<IdResponse> create(@RequestBody Employee employee) {
        Integer id = employeeService.create(employee);
        return new ResponseEntity<>(new IdResponse(id), HttpStatus.CREATED);
    }

    @PatchMapping("/{id}")
    public Employee updateSelective(@PathVariable("id") Integer id, @RequestBody Employee employee) {
        return employeeService.updateSelective(id, employee);
    }

    @DeleteMapping("/{id}")
    public Map<String, Object> delete(@PathVariable("id") Integer id) {
        employeeService.deleteById(id);
        Map<String, Object> body = new LinkedHashMap<>();
        body.put("message", "删除成功");
        return body;
    }

    @GetMapping("/search")
    public PagedResult<Employee> search(@RequestParam(value = "keyword", required = false) String keyword,
                                        @RequestParam(value = "deptId", required = false) Integer deptId,
                                        @RequestParam(value = "minSalary", required = false) BigDecimal minSalary,
                                        @RequestParam(value = "maxSalary", required = false) BigDecimal maxSalary,
                                        @RequestParam(value = "page", defaultValue = "1") int page,
                                        @RequestParam(value = "pageSize", defaultValue = "10") int pageSize) {
        return employeeService.search(keyword, deptId, minSalary, maxSalary, page, pageSize);
    }

    @GetMapping("/{id}/detail")
    public Employee getDetail(@PathVariable("id") Integer id) {
        return employeeService.getDetail(id);
    }

    @GetMapping("/{id}/detail-lazy")
    public EmployeeDetailLazyResponse getDetailLazy(@PathVariable("id") Integer id) {
        Employee employee = employeeService.getDetail(id);
        EmployeeDetailLazyResponse resp = new EmployeeDetailLazyResponse();
        resp.setEmpId(employee.getEmpId());
        resp.setEmpName(employee.getEmpName());
        resp.setGender(employee.getGender());
        resp.setEmail(employee.getEmail());
        resp.setPhone(employee.getPhone());
        resp.setHireDate(employee.getHireDate());
        resp.setSalary(employee.getSalary());
        resp.setDeptId(employee.getDeptId());
        resp.setDepartment(employee.getDepartment());
        return resp;
    }

    @PostMapping("/transaction-test")
    public ResponseEntity<IdResponse> transactionTest(@RequestBody Employee employee) {
        Integer id = employeeService.createAndFailForTransactionTest(employee);
        return new ResponseEntity<>(new IdResponse(id), HttpStatus.CREATED);
    }
}

