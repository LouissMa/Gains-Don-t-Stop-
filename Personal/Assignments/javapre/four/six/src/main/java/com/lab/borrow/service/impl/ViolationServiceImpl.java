package com.lab.borrow.service.impl;

import com.lab.borrow.common.BizException;
import com.lab.borrow.common.PageResult;
import com.lab.borrow.domain.Const;
import com.lab.borrow.entity.BorrowApply;
import com.lab.borrow.entity.Device;
import com.lab.borrow.entity.Violation;
import com.lab.borrow.entity.ViolationStat;
import com.lab.borrow.mapper.BorrowApplyMapper;
import com.lab.borrow.mapper.DeviceMapper;
import com.lab.borrow.mapper.ViolationMapper;
import com.lab.borrow.service.ViolationService;
import com.lab.borrow.util.ValidationUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import javax.annotation.Resource;
import java.time.LocalDate;
import java.time.temporal.ChronoUnit;
import java.util.Date;
import java.util.List;

@Service
public class ViolationServiceImpl implements ViolationService {
    private static final Logger log = LoggerFactory.getLogger(ViolationServiceImpl.class);

    @Resource
    private BorrowApplyMapper borrowApplyMapper;

    @Resource
    private ViolationMapper violationMapper;

    @Resource
    private DeviceMapper deviceMapper;

    @Override
    @Transactional
    public void detectOverdue() {
        LocalDate today = LocalDate.now();
        List<BorrowApply> overdue = borrowApplyMapper.listOverdueBorrowed(today);
        for (BorrowApply apply : overdue) {
            ensureViolationExists(apply, today);
        }
    }

    @Override
    public long countUntreatedByUserId(Integer userId) {
        ValidationUtils.require(userId != null, "用户ID不能为空");
        return violationMapper.countUntreatedByUserId(userId);
    }

    @Override
    public PageResult<Violation> pageForAdmin(Integer userId, Integer deviceId, String status, int page, int size) {
        int safePage = Math.max(page, 1);
        int safeSize = Math.min(Math.max(size, 1), 50);
        int offset = (safePage - 1) * safeSize;

        long total = violationMapper.count(userId, deviceId, emptyToNull(status));
        List<Violation> list = violationMapper.page(userId, deviceId, emptyToNull(status), offset, safeSize);
        fillCurrentOverdueDays(list);
        return new PageResult<>(list, total, safePage, safeSize);
    }

    @Override
    public PageResult<Violation> pageForUser(Integer userId, String status, int page, int size) {
        ValidationUtils.require(userId != null, "用户ID不能为空");
        return pageForAdmin(userId, null, status, page, size);
    }

    @Override
    public Violation getById(Integer violationId) {
        ValidationUtils.require(violationId != null, "违规ID不能为空");
        Violation v = violationMapper.selectById(violationId);
        ValidationUtils.require(v != null, "违规记录不存在");
        fillCurrentOverdueDays(v);
        return v;
    }

    @Override
    @Transactional
    public void process(Integer violationId, Integer adminUserId, String processNote) {
        ValidationUtils.require(violationId != null, "违规ID不能为空");
        ValidationUtils.require(adminUserId != null, "处理人不能为空");
        ValidationUtils.requireNotBlank(processNote, "处理备注不能为空");
        ValidationUtils.requireMaxLength(processNote, 500, "处理备注长度不能超过500字符");

        Violation v = violationMapper.selectById(violationId);
        ValidationUtils.require(v != null, "违规记录不存在");
        ValidationUtils.require(Const.VIOLATION_STATUS_UNTREATED.equals(v.getStatus()), "该违规已处理，不能重复处理");

        int updated = violationMapper.updateProcessed(violationId, new Date(), adminUserId, processNote.trim());
        if (updated != 1) {
            throw new BizException("处理失败，请刷新后重试");
        }
        log.info("管理员{}处理违规{}，备注：{}", adminUserId, violationId, processNote.trim());
    }

    @Override
    @Transactional
    public void autoProcessOnReturn(Integer borrowRecordId, Integer adminUserId) {
        ValidationUtils.require(borrowRecordId != null, "借用记录ID不能为空");
        ValidationUtils.require(adminUserId != null, "处理人不能为空");

        BorrowApply apply = borrowApplyMapper.selectById(borrowRecordId);
        if (apply == null) {
            return;
        }

        LocalDate today = LocalDate.now();
        if (apply.getEndDate() == null || !apply.getEndDate().isBefore(today)) {
            return;
        }

        Violation v = ensureViolationExists(apply, today);
        if (v == null) {
            return;
        }
        if (!Const.VIOLATION_STATUS_UNTREATED.equals(v.getStatus())) {
            return;
        }

        int updated = violationMapper.updateProcessed(v.getViolationId(), new Date(), adminUserId, "设备已归还，系统自动处理");
        if (updated == 1) {
            log.info("归还时自动处理违规{}（借用记录{}）", v.getViolationId(), borrowRecordId);
        }
    }

    @Override
    public List<ViolationStat> statsByUser() {
        return violationMapper.statsByUser();
    }

    @Override
    public List<ViolationStat> statsByDevice() {
        return violationMapper.statsByDevice();
    }

    @Override
    public DeviceUsageRate usageRate(Integer deviceId, LocalDate startDate, LocalDate endDate) {
        ValidationUtils.require(deviceId != null, "设备ID不能为空");
        ValidationUtils.require(startDate != null, "开始日期不能为空");
        ValidationUtils.require(endDate != null, "结束日期不能为空");
        ValidationUtils.require(endDate.isAfter(startDate), "结束日期必须晚于开始日期");

        long totalDays = ChronoUnit.DAYS.between(startDate, endDate);
        ValidationUtils.require(totalDays > 0, "查询区间不合法");
        ValidationUtils.require(totalDays <= 365, "查询区间不超过365天");

        Device device = deviceMapper.selectById(deviceId);
        ValidationUtils.require(device != null, "设备不存在");

        long borrowedDays = violationMapper.sumDeviceBorrowDaysInRange(deviceId, startDate, endDate);
        DeviceUsageRate result = new DeviceUsageRate();
        result.setDeviceId(deviceId);
        result.setDeviceName(device.getDeviceName());
        result.setBorrowedDays(borrowedDays);
        result.setTotalDays(totalDays);
        result.setRatio(totalDays == 0 ? 0.0 : borrowedDays * 1.0 / totalDays);
        return result;
    }

    private Violation ensureViolationExists(BorrowApply apply, LocalDate today) {
        if (apply.getApplyId() == null || apply.getEndDate() == null) {
            return null;
        }
        if (!apply.getEndDate().isBefore(today)) {
            return null;
        }
        Violation existing = violationMapper.selectByBorrowRecordId(apply.getApplyId());
        if (existing != null) {
            return existing;
        }

        long overdueDays = ChronoUnit.DAYS.between(apply.getEndDate(), today);
        if (overdueDays < 0) {
            overdueDays = 0;
        }

        Violation v = new Violation();
        v.setUserId(apply.getUserId());
        v.setDeviceId(apply.getDeviceId());
        v.setBorrowRecordId(apply.getApplyId());
        v.setViolationStartDate(apply.getEndDate().plusDays(1));
        v.setViolationDays((int) Math.min(overdueDays, Integer.MAX_VALUE));
        v.setStatus(Const.VIOLATION_STATUS_UNTREATED);
        violationMapper.insert(v);
        log.info("生成违规记录{}：用户{} 设备{} 借用记录{} 超时{}天", v.getViolationId(), v.getUserId(), v.getDeviceId(), v.getBorrowRecordId(), v.getViolationDays());
        return violationMapper.selectByBorrowRecordId(apply.getApplyId());
    }

    private void fillCurrentOverdueDays(List<Violation> list) {
        if (list == null) {
            return;
        }
        for (Violation v : list) {
            fillCurrentOverdueDays(v);
        }
    }

    private void fillCurrentOverdueDays(Violation v) {
        if (v == null || v.getEndDate() == null) {
            return;
        }
        LocalDate today = LocalDate.now();
        long days = ChronoUnit.DAYS.between(v.getEndDate(), today);
        v.setCurrentOverdueDays(Math.max(days, 0));
    }

    private String emptyToNull(String value) {
        return value == null || value.trim().isEmpty() ? null : value.trim();
    }
}
