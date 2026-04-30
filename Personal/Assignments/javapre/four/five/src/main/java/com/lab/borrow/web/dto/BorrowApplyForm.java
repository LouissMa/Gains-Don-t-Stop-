package com.lab.borrow.web.dto;

import org.springframework.format.annotation.DateTimeFormat;

import javax.validation.constraints.NotNull;
import javax.validation.constraints.Size;
import java.time.LocalDate;

public class BorrowApplyForm {
    @NotNull(message = "设备ID不能为空")
    private Integer deviceId;

    @NotNull(message = "计划借用开始日期不能为空")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDate startDate;

    @NotNull(message = "计划归还日期不能为空")
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDate endDate;

    @NotNull(message = "借用用途不能为空")
    private String purposeType;

    @Size(max = 500, message = "用途说明长度不能超过500字符")
    private String purposeNote;

    public Integer getDeviceId() {
        return deviceId;
    }

    public void setDeviceId(Integer deviceId) {
        this.deviceId = deviceId;
    }

    public LocalDate getStartDate() {
        return startDate;
    }

    public void setStartDate(LocalDate startDate) {
        this.startDate = startDate;
    }

    public LocalDate getEndDate() {
        return endDate;
    }

    public void setEndDate(LocalDate endDate) {
        this.endDate = endDate;
    }

    public String getPurposeType() {
        return purposeType;
    }

    public void setPurposeType(String purposeType) {
        this.purposeType = purposeType;
    }

    public String getPurposeNote() {
        return purposeNote;
    }

    public void setPurposeNote(String purposeNote) {
        this.purposeNote = purposeNote;
    }
}
