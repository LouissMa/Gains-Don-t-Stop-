package com.lab.borrow.web.dto;

import org.springframework.format.annotation.DateTimeFormat;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;
import java.util.Date;

public class DeviceForm {
    private Integer deviceId;

    @NotBlank
    private String deviceName;

    @NotBlank
    private String deviceModel;

    @NotNull
    private Integer categoryId;

    @NotBlank
    private String location;

    @NotNull
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private Date purchaseDate;

    @NotBlank
    private String status;

    @NotNull
    private Integer maxBorrowDays;

    public Integer getDeviceId() {
        return deviceId;
    }

    public void setDeviceId(Integer deviceId) {
        this.deviceId = deviceId;
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

    public Integer getCategoryId() {
        return categoryId;
    }

    public void setCategoryId(Integer categoryId) {
        this.categoryId = categoryId;
    }

    public String getLocation() {
        return location;
    }

    public void setLocation(String location) {
        this.location = location;
    }

    public Date getPurchaseDate() {
        return purchaseDate;
    }

    public void setPurchaseDate(Date purchaseDate) {
        this.purchaseDate = purchaseDate;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public Integer getMaxBorrowDays() {
        return maxBorrowDays;
    }

    public void setMaxBorrowDays(Integer maxBorrowDays) {
        this.maxBorrowDays = maxBorrowDays;
    }
}
