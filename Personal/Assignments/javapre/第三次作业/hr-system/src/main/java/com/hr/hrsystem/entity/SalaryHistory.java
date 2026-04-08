package com.hr.hrsystem.entity;

import com.fasterxml.jackson.annotation.JsonFormat;

import java.math.BigDecimal;
import java.util.Date;

public class SalaryHistory {
    private Integer id;
    private Integer empId;
    private BigDecimal oldSalary;
    private BigDecimal newSalary;

    @JsonFormat(pattern = "yyyy-MM-dd", timezone = "Asia/Shanghai")
    private Date adjustDate;

    private String reason;

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public Integer getEmpId() {
        return empId;
    }

    public void setEmpId(Integer empId) {
        this.empId = empId;
    }

    public BigDecimal getOldSalary() {
        return oldSalary;
    }

    public void setOldSalary(BigDecimal oldSalary) {
        this.oldSalary = oldSalary;
    }

    public BigDecimal getNewSalary() {
        return newSalary;
    }

    public void setNewSalary(BigDecimal newSalary) {
        this.newSalary = newSalary;
    }

    public Date getAdjustDate() {
        return adjustDate;
    }

    public void setAdjustDate(Date adjustDate) {
        this.adjustDate = adjustDate;
    }

    public String getReason() {
        return reason;
    }

    public void setReason(String reason) {
        this.reason = reason;
    }
}
