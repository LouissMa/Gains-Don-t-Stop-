package com.lab.borrow.service;

import com.lab.borrow.common.PageResult;
import com.lab.borrow.entity.BorrowApply;
import com.lab.borrow.entity.DashboardStats;

import java.time.LocalDate;

public interface BorrowApplyService {
    BorrowApply submit(Integer userId, Integer deviceId, LocalDate startDate, LocalDate endDate, String purposeType, String purposeNote);

    void approve(Integer applyId, Integer adminUserId, String auditNote);

    void reject(Integer applyId, Integer adminUserId, String auditNote);

    void confirmBorrow(Integer applyId, Integer adminUserId);

    void confirmReturn(Integer applyId, Integer adminUserId, String returnNote);

    void cancel(Integer applyId, Integer userId);

    BorrowApply getById(Integer applyId);

    PageResult<BorrowApply> pageForUser(Integer userId, String status, int page, int size);

    PageResult<BorrowApply> pageForAdmin(String status, int page, int size);

    DashboardStats dashboard();
}
