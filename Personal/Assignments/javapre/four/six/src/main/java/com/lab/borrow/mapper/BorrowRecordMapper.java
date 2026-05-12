package com.lab.borrow.mapper;

import org.apache.ibatis.annotations.Param;

public interface BorrowRecordMapper {
    long countActiveByUserId(@Param("userId") Integer userId);

    long countAnyByUserId(@Param("userId") Integer userId);

    long countActiveByDeviceId(@Param("deviceId") Integer deviceId);
}
