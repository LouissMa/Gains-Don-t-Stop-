package com.lab.borrow.mapper;

import com.lab.borrow.entity.BorrowApply;
import org.apache.ibatis.annotations.Param;

import java.time.LocalDate;
import java.util.List;

public interface BorrowApplyMapper {
    int insert(BorrowApply apply);

    BorrowApply selectById(@Param("applyId") Integer applyId);

    int updateStatus(BorrowApply apply);

    List<BorrowApply> page(@Param("userId") Integer userId,
                           @Param("status") String status,
                           @Param("offset") int offset,
                           @Param("size") int size);

    long count(@Param("userId") Integer userId, @Param("status") String status);

    long countByStatus(@Param("status") String status);

    long countToday();

    long countActiveByUserId(@Param("userId") Integer userId);

    long countAnyByUserId(@Param("userId") Integer userId);

    long countActiveByDeviceId(@Param("deviceId") Integer deviceId);

    long countConflict(@Param("deviceId") Integer deviceId,
                       @Param("startDate") LocalDate startDate,
                       @Param("endDate") LocalDate endDate,
                       @Param("statuses") List<String> statuses,
                       @Param("excludeApplyId") Integer excludeApplyId);

    List<BorrowApply> listOverdueBorrowed(@Param("today") LocalDate today);
}
