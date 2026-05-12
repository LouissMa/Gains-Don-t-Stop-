package com.lab.borrow.entity;

import java.time.LocalDate;
import java.util.Date;

public class Violation {
    private Integer violationId;
    private Integer userId;
    private Integer deviceId;
    private Integer borrowRecordId;
    private LocalDate violationStartDate;
    private Integer violationDays;
    private String status;
    private Date processDate;
    private Integer processUserId;
    private String processNote;

    private String username;
    private String realName;
    private String deviceName;
    private String deviceModel;
    private LocalDate endDate;
    private Long currentOverdueDays;

    public Integer getViolationId() {
        return violationId;
    }

    public void setViolationId(Integer violationId) {
        this.violationId = violationId;
    }

    public Integer getUserId() {
        return userId;
    }

    public void setUserId(Integer userId) {
        this.userId = userId;
    }

    public Integer getDeviceId() {
        return deviceId;
    }

    public void setDeviceId(Integer deviceId) {
        this.deviceId = deviceId;
    }

    public Integer getBorrowRecordId() {
        return borrowRecordId;
    }

    public void setBorrowRecordId(Integer borrowRecordId) {
        this.borrowRecordId = borrowRecordId;
    }

    public LocalDate getViolationStartDate() {
        return violationStartDate;
    }

    public void setViolationStartDate(LocalDate violationStartDate) {
        this.violationStartDate = violationStartDate;
    }

    public Integer getViolationDays() {
        return violationDays;
    }

    public void setViolationDays(Integer violationDays) {
        this.violationDays = violationDays;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public Date getProcessDate() {
        return processDate;
    }

    public void setProcessDate(Date processDate) {
        this.processDate = processDate;
    }

    public Integer getProcessUserId() {
        return processUserId;
    }

    public void setProcessUserId(Integer processUserId) {
        this.processUserId = processUserId;
    }

    public String getProcessNote() {
        return processNote;
    }

    public void setProcessNote(String processNote) {
        this.processNote = processNote;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getRealName() {
        return realName;
    }

    public void setRealName(String realName) {
        this.realName = realName;
    }

    public String getDeviceName() {
        return deviceName;
    }

    public void setDeviceName(String deviceName) {
        this.deviceName = deviceName;
    }

    public String getDeviceModel() {
        return deviceModel;
    }

    public void setDeviceModel(String deviceModel) {
        this.deviceModel = deviceModel;
    }

    public LocalDate getEndDate() {
        return endDate;
    }

    public void setEndDate(LocalDate endDate) {
        this.endDate = endDate;
    }

    public Long getCurrentOverdueDays() {
        return currentOverdueDays;
    }

    public void setCurrentOverdueDays(Long currentOverdueDays) {
        this.currentOverdueDays = currentOverdueDays;
    }
}
