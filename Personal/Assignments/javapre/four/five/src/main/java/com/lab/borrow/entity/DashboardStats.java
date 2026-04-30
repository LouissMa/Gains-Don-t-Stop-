package com.lab.borrow.entity;

import java.util.LinkedHashMap;
import java.util.Map;

public class DashboardStats {
    private long pendingApplyCount;
    private long borrowedApplyCount;
    private long todayApplyCount;
    private Map<String, Long> deviceStatusCounts = new LinkedHashMap<>();

    public long getPendingApplyCount() {
        return pendingApplyCount;
    }

    public void setPendingApplyCount(long pendingApplyCount) {
        this.pendingApplyCount = pendingApplyCount;
    }

    public long getBorrowedApplyCount() {
        return borrowedApplyCount;
    }

    public void setBorrowedApplyCount(long borrowedApplyCount) {
        this.borrowedApplyCount = borrowedApplyCount;
    }

    public long getTodayApplyCount() {
        return todayApplyCount;
    }

    public void setTodayApplyCount(long todayApplyCount) {
        this.todayApplyCount = todayApplyCount;
    }

    public Map<String, Long> getDeviceStatusCounts() {
        return deviceStatusCounts;
    }

    public void setDeviceStatusCounts(Map<String, Long> deviceStatusCounts) {
        this.deviceStatusCounts = deviceStatusCounts;
    }
}
