package com.lab.borrow.mapper;

import com.lab.borrow.entity.Device;
import org.apache.ibatis.annotations.Param;

import java.util.List;

public interface DeviceMapper {
    int insert(Device device);

    Device selectById(@Param("deviceId") Integer deviceId);

    Device selectByName(@Param("deviceName") String deviceName);

    int updateById(Device device);

    int updateStatus(@Param("deviceId") Integer deviceId, @Param("status") String status);

    int deleteById(@Param("deviceId") Integer deviceId);

    List<Device> page(@Param("categoryId") Integer categoryId, @Param("keyword") String keyword, @Param("offset") int offset, @Param("size") int size);

    long count(@Param("categoryId") Integer categoryId, @Param("keyword") String keyword);

    long countByCategoryId(@Param("categoryId") Integer categoryId);

    long countByStatus(@Param("status") String status);
}
