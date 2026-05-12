package com.lab.borrow.entity;

public class OverdueItem {
    private BorrowApply apply;
    private Integer violationId;
    private Long overdueDays;

    public BorrowApply getApply() {
        return apply;
    }

    public void setApply(BorrowApply apply) {
        this.apply = apply;
    }

    public Integer getViolationId() {
        return violationId;
    }

    public void setViolationId(Integer violationId) {
        this.violationId = violationId;
    }

    public Long getOverdueDays() {
        return overdueDays;
    }

    public void setOverdueDays(Long overdueDays) {
        this.overdueDays = overdueDays;
    }
}
