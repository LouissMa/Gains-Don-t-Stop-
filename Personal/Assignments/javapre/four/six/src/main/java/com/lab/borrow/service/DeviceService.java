package com.lab.borrow.service;

import com.lab.borrow.common.PageResult;
import com.lab.borrow.entity.Device;

public interface DeviceService {
    Device create(Device device);

    Device update(Device device);

    void delete(Integer deviceId);

    Device getById(Integer deviceId);

    PageResult<Device> page(Integer categoryId, String keyword, int page, int size);
}
