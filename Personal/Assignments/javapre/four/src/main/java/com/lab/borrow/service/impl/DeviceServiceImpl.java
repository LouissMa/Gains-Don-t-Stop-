package com.lab.borrow.service.impl;

import com.lab.borrow.common.BizException;
import com.lab.borrow.common.PageResult;
import com.lab.borrow.domain.Const;
import com.lab.borrow.entity.Category;
import com.lab.borrow.entity.Device;
import com.lab.borrow.mapper.BorrowRecordMapper;
import com.lab.borrow.mapper.CategoryMapper;
import com.lab.borrow.mapper.DeviceMapper;
import com.lab.borrow.service.DeviceService;
import com.lab.borrow.util.ValidationUtils;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import javax.annotation.Resource;
import java.util.Date;
import java.util.List;

@Service
public class DeviceServiceImpl implements DeviceService {
    @Resource
    private DeviceMapper deviceMapper;

    @Resource
    private CategoryMapper categoryMapper;

    @Resource
    private BorrowRecordMapper borrowRecordMapper;

    @Override
    @Transactional
    public Device create(Device device) {
        ValidationUtils.require(device != null, "设备信息不能为空");
        validateDeviceForCreate(device);

        Device existing = deviceMapper.selectByName(device.getDeviceName());
        ValidationUtils.require(existing == null, "设备名称已存在");

        deviceMapper.insert(device);
        return deviceMapper.selectById(device.getDeviceId());
    }

    @Override
    @Transactional
    public Device update(Device device) {
        ValidationUtils.require(device != null, "设备信息不能为空");
        ValidationUtils.require(device.getDeviceId() != null, "设备ID不能为空");

        Device existing = deviceMapper.selectById(device.getDeviceId());
        ValidationUtils.require(existing != null, "设备不存在");

        validateDeviceForUpdate(device, existing);

        Device byName = deviceMapper.selectByName(device.getDeviceName());
        if (byName != null && !byName.getDeviceId().equals(device.getDeviceId())) {
            throw new BizException("设备名称已存在");
        }

        deviceMapper.updateById(device);
        return deviceMapper.selectById(device.getDeviceId());
    }

    @Override
    @Transactional
    public void delete(Integer deviceId) {
        ValidationUtils.require(deviceId != null, "设备ID不能为空");
        Device existing = deviceMapper.selectById(deviceId);
        ValidationUtils.require(existing != null, "设备不存在");

        long activeBorrow = borrowRecordMapper.countActiveByDeviceId(deviceId);
        ValidationUtils.require(activeBorrow == 0, "该设备存在进行中的借用记录，禁止删除");

        deviceMapper.deleteById(deviceId);
    }

    @Override
    public Device getById(Integer deviceId) {
        ValidationUtils.require(deviceId != null, "设备ID不能为空");
        Device device = deviceMapper.selectById(deviceId);
        ValidationUtils.require(device != null, "设备不存在");
        return device;
    }

    @Override
    public PageResult<Device> page(Integer categoryId, String keyword, int page, int size) {
        int safePage = Math.max(page, 1);
        int safeSize = Math.min(Math.max(size, 1), 50);
        int offset = (safePage - 1) * safeSize;

        if (categoryId != null) {
            Category category = categoryMapper.selectById(categoryId);
            ValidationUtils.require(category != null, "分类不存在");
        }

        long total = deviceMapper.count(categoryId, keyword);
        List<Device> list = deviceMapper.page(categoryId, keyword, offset, safeSize);
        return new PageResult<>(list, total, safePage, safeSize);
    }

    private void validateDeviceForCreate(Device device) {
        ValidationUtils.requireNotBlank(device.getDeviceName(), "设备名称不能为空");
        ValidationUtils.requireMaxLength(device.getDeviceName(), 100, "设备名称长度不能超过100");
        ValidationUtils.requireNotBlank(device.getDeviceModel(), "设备型号不能为空");
        ValidationUtils.requireMaxLength(device.getDeviceModel(), 100, "设备型号长度不能超过100");
        ValidationUtils.require(device.getCategoryId() != null, "分类不能为空");
        Category category = categoryMapper.selectById(device.getCategoryId());
        ValidationUtils.require(category != null, "分类不存在");
        ValidationUtils.requireNotBlank(device.getLocation(), "存放位置不能为空");
        ValidationUtils.requireMaxLength(device.getLocation(), 100, "存放位置长度不能超过100");
        ValidationUtils.requireNotFuture(device.getPurchaseDate(), "购入日期不能为空且不能晚于当前日期");
        ValidationUtils.requireNotBlank(device.getStatus(), "设备状态不能为空");
        ValidationUtils.require(isAllowedDeviceStatusForManual(device.getStatus()), "设备状态只能是available/maintenance/retired");
        ValidationUtils.require(!Const.DEVICE_STATUS_BORROWED.equals(device.getStatus()), "新增设备状态不能为borrowed");
        ValidationUtils.requirePositiveInt(device.getMaxBorrowDays(), "单次最长借用天数必须为正整数");
        ValidationUtils.require(device.getMaxBorrowDays() <= 365, "单次最长借用天数建议范围1~365");
    }

    private void validateDeviceForUpdate(Device device, Device existing) {
        ValidationUtils.requireNotBlank(device.getDeviceName(), "设备名称不能为空");
        ValidationUtils.requireMaxLength(device.getDeviceName(), 100, "设备名称长度不能超过100");
        ValidationUtils.requireNotBlank(device.getDeviceModel(), "设备型号不能为空");
        ValidationUtils.requireMaxLength(device.getDeviceModel(), 100, "设备型号长度不能超过100");
        ValidationUtils.require(device.getCategoryId() != null, "分类不能为空");
        Category category = categoryMapper.selectById(device.getCategoryId());
        ValidationUtils.require(category != null, "分类不存在");
        ValidationUtils.requireNotBlank(device.getLocation(), "存放位置不能为空");
        ValidationUtils.requireMaxLength(device.getLocation(), 100, "存放位置长度不能超过100");
        ValidationUtils.requireNotFuture(device.getPurchaseDate(), "购入日期不能为空且不能晚于当前日期");
        ValidationUtils.requirePositiveInt(device.getMaxBorrowDays(), "单次最长借用天数必须为正整数");

        if (device.getStatus() != null && !device.getStatus().trim().isEmpty()) {
            ValidationUtils.require(isAllowedDeviceStatusForManual(device.getStatus()), "设备状态只能是available/maintenance/retired");
        }

        if (Const.DEVICE_STATUS_BORROWED.equals(existing.getStatus())) {
            String newStatus = device.getStatus();
            if (newStatus != null && !newStatus.equals(existing.getStatus())) {
                throw new BizException("设备当前为borrowed，禁止手动修改状态");
            }
            device.setStatus(existing.getStatus());
        } else {
            if (device.getStatus() == null || device.getStatus().trim().isEmpty()) {
                device.setStatus(existing.getStatus());
            }
            if (Const.DEVICE_STATUS_BORROWED.equals(device.getStatus())) {
                throw new BizException("设备状态不能手动设置为borrowed");
            }
        }
    }

    private boolean isAllowedDeviceStatusForManual(String status) {
        return Const.DEVICE_STATUS_AVAILABLE.equals(status)
                || Const.DEVICE_STATUS_MAINTENANCE.equals(status)
                || Const.DEVICE_STATUS_RETIRED.equals(status);
    }
}
