package com.lab.borrow.mapper;

import com.lab.borrow.entity.Violation;
import com.lab.borrow.entity.ViolationStat;
import org.apache.ibatis.annotations.Param;

import java.time.LocalDate;
import java.util.Date;
import java.util.List;

public interface ViolationMapper {
    int insert(Violation violation);

    Violation selectById(@Param("violationId") Integer violationId);

    Violation selectByBorrowRecordId(@Param("borrowRecordId") Integer borrowRecordId);

    int updateProcessed(@Param("violationId") Integer violationId,
                        @Param("processDate") Date processDate,
                        @Param("processUserId") Integer processUserId,
                        @Param("processNote") String processNote);

    List<Violation> page(@Param("userId") Integer userId,
                         @Param("deviceId") Integer deviceId,
                         @Param("status") String status,
                         @Param("offset") int offset,
                         @Param("size") int size);

    long count(@Param("userId") Integer userId,
               @Param("deviceId") Integer deviceId,
               @Param("status") String status);

    long countUntreatedByUserId(@Param("userId") Integer userId);

    List<ViolationStat> statsByUser();

    List<ViolationStat> statsByDevice();

    long sumDeviceBorrowDaysInRange(@Param("deviceId") Integer deviceId,
                                    @Param("startDate") LocalDate startDate,
                                    @Param("endDate") LocalDate endDate);
}
