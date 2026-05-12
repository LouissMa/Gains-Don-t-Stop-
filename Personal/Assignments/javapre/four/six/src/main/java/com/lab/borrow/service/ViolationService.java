package com.lab.borrow.service;

import com.lab.borrow.common.PageResult;
import com.lab.borrow.entity.Violation;
import com.lab.borrow.entity.ViolationStat;

import java.time.LocalDate;
import java.util.List;

public interface ViolationService {
    void detectOverdue();

    long countUntreatedByUserId(Integer userId);

    PageResult<Violation> pageForAdmin(Integer userId, Integer deviceId, String status, int page, int size);

    PageResult<Violation> pageForUser(Integer userId, String status, int page, int size);

    Violation getById(Integer violationId);

    void process(Integer violationId, Integer adminUserId, String processNote);

    void autoProcessOnReturn(Integer borrowRecordId, Integer adminUserId);

    List<ViolationStat> statsByUser();

    List<ViolationStat> statsByDevice();

    DeviceUsageRate usageRate(Integer deviceId, LocalDate startDate, LocalDate endDate);

    class DeviceUsageRate {
        private Integer deviceId;
        private String deviceName;
        private long borrowedDays;
        private long totalDays;
        private double ratio;

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

        public long getBorrowedDays() {
            return borrowedDays;
        }

        public void setBorrowedDays(long borrowedDays) {
            this.borrowedDays = borrowedDays;
        }

        public long getTotalDays() {
            return totalDays;
        }

        public void setTotalDays(long totalDays) {
            this.totalDays = totalDays;
        }

        public double getRatio() {
            return ratio;
        }

        public void setRatio(double ratio) {
            this.ratio = ratio;
        }
    }
}
