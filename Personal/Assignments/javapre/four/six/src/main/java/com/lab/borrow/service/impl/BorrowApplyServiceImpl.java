package com.lab.borrow.service.impl;

import com.lab.borrow.common.BizException;
import com.lab.borrow.common.PageResult;
import com.lab.borrow.domain.Const;
import com.lab.borrow.entity.BorrowApply;
import com.lab.borrow.entity.DashboardStats;
import com.lab.borrow.entity.Device;
import com.lab.borrow.mapper.BorrowApplyMapper;
import com.lab.borrow.mapper.DeviceMapper;
import com.lab.borrow.service.BorrowApplyService;
import com.lab.borrow.service.ViolationService;
import com.lab.borrow.util.ValidationUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import javax.annotation.Resource;
import java.time.LocalDate;
import java.time.temporal.ChronoUnit;
import java.util.Arrays;
import java.util.Date;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

@Service
public class BorrowApplyServiceImpl implements BorrowApplyService {
    private static final Logger log = LoggerFactory.getLogger(BorrowApplyServiceImpl.class);
    private static final List<String> APPLY_CONFLICT_STATUS =
            Arrays.asList(Const.APPLY_STATUS_PENDING, Const.APPLY_STATUS_APPROVED, Const.APPLY_STATUS_BORROWED);
    private static final List<String> APPROVE_CONFLICT_STATUS =
            Arrays.asList(Const.APPLY_STATUS_APPROVED, Const.APPLY_STATUS_BORROWED);

    @Resource
    private BorrowApplyMapper borrowApplyMapper;

    @Resource
    private DeviceMapper deviceMapper;

    @Resource
    private ViolationService violationService;

    @Override
    @Transactional
    public BorrowApply submit(Integer userId, Integer deviceId, LocalDate startDate, LocalDate endDate, String purposeType, String purposeNote) {
        ValidationUtils.require(userId != null, "申请人不能为空");
        if (violationService.countUntreatedByUserId(userId) > 0) {
            throw new BizException("您有待处理的违规记录，无法申请借用设备");
        }
        Device device = validateApplyFields(deviceId, startDate, endDate, purposeType, purposeNote);

        int borrowDays = calculateBorrowDays(startDate, endDate);
        ValidationUtils.require(borrowDays <= device.getMaxBorrowDays(), "借用天数不能超过该设备允许的最大天数：" + device.getMaxBorrowDays() + "天");
        assertNoConflict(deviceId, startDate, endDate, APPLY_CONFLICT_STATUS, null);

        BorrowApply apply = new BorrowApply();
        apply.setUserId(userId);
        apply.setDeviceId(deviceId);
        apply.setStartDate(startDate);
        apply.setEndDate(endDate);
        apply.setBorrowDays(borrowDays);
        apply.setPurposeType(purposeType);
        apply.setPurposeNote(trimToNull(purposeNote));
        apply.setStatus(Const.APPLY_STATUS_PENDING);
        borrowApplyMapper.insert(apply);
        log.info("用户{}提交借用申请{}，设备{}，{}至{}", userId, apply.getApplyId(), deviceId, startDate, endDate);
        return borrowApplyMapper.selectById(apply.getApplyId());
    }

    @Override
    @Transactional
    public void approve(Integer applyId, Integer adminUserId, String auditNote) {
        BorrowApply apply = requireApply(applyId);
        requireStatus(apply, Const.APPLY_STATUS_PENDING, "只有待审批申请可以批准");
        Device device = deviceMapper.selectById(apply.getDeviceId());
        ValidationUtils.require(device != null, "设备不存在");
        ValidationUtils.require(Const.DEVICE_STATUS_AVAILABLE.equals(device.getStatus()), "设备当前不可借用");
        assertNoConflict(apply.getDeviceId(), apply.getStartDate(), apply.getEndDate(), APPROVE_CONFLICT_STATUS, applyId);

        updateApplyStatus(applyId, Const.APPLY_STATUS_APPROVED, adminUserId, trimToNull(auditNote), null, null, null);
        log.info("管理员{}批准申请{}", adminUserId, applyId);
    }

    @Override
    @Transactional
    public void reject(Integer applyId, Integer adminUserId, String auditNote) {
        BorrowApply apply = requireApply(applyId);
        requireStatus(apply, Const.APPLY_STATUS_PENDING, "只有待审批申请可以驳回");
        ValidationUtils.requireNotBlank(auditNote, "驳回原因不能为空");
        ValidationUtils.requireMaxLength(auditNote, 500, "驳回原因长度不能超过500字符");
        updateApplyStatus(applyId, Const.APPLY_STATUS_REJECTED, adminUserId, auditNote.trim(), null, null, null);
        log.info("管理员{}驳回申请{}，原因：{}", adminUserId, applyId, auditNote.trim());
    }

    @Override
    @Transactional
    public void confirmBorrow(Integer applyId, Integer adminUserId) {
        BorrowApply apply = requireApply(applyId);
        requireStatus(apply, Const.APPLY_STATUS_APPROVED, "只有已批准申请可以确认借出");
        Device device = deviceMapper.selectById(apply.getDeviceId());
        ValidationUtils.require(device != null, "设备不存在");
        ValidationUtils.require(Const.DEVICE_STATUS_AVAILABLE.equals(device.getStatus()), "设备当前不可借出");

        Date now = new Date();
        updateApplyStatus(applyId, Const.APPLY_STATUS_BORROWED, adminUserId, apply.getAuditNote(), now, null, null);
        deviceMapper.updateStatus(apply.getDeviceId(), Const.DEVICE_STATUS_BORROWED);
        log.info("管理员{}确认借出申请{}，设备{}", adminUserId, applyId, apply.getDeviceId());
    }

    @Override
    @Transactional
    public void confirmReturn(Integer applyId, Integer adminUserId, String returnNote) {
        BorrowApply apply = requireApply(applyId);
        requireStatus(apply, Const.APPLY_STATUS_BORROWED, "只有借出中申请可以确认归还");
        ValidationUtils.requireNotBlank(returnNote, "归还备注不能为空");
        ValidationUtils.requireMaxLength(returnNote, 500, "归还备注长度不能超过500字符");

        Date now = new Date();
        updateApplyStatus(applyId, Const.APPLY_STATUS_RETURNED, adminUserId, apply.getAuditNote(), null, now, returnNote.trim());
        deviceMapper.updateStatus(apply.getDeviceId(), Const.DEVICE_STATUS_AVAILABLE);
        violationService.autoProcessOnReturn(applyId, adminUserId);
        log.info("管理员{}确认归还申请{}，设备{}，备注：{}", adminUserId, applyId, apply.getDeviceId(), returnNote.trim());
    }

    @Override
    @Transactional
    public void cancel(Integer applyId, Integer userId) {
        BorrowApply apply = requireApply(applyId);
        requireStatus(apply, Const.APPLY_STATUS_PENDING, "只有待审批申请可以取消");
        ValidationUtils.require(apply.getUserId().equals(userId), "只能取消本人提交的申请");
        updateApplyStatus(applyId, Const.APPLY_STATUS_CANCELLED, null, null, null, null, null);
        log.info("用户{}取消申请{}", userId, applyId);
    }

    @Override
    public BorrowApply getById(Integer applyId) {
        return requireApply(applyId);
    }

    @Override
    public PageResult<BorrowApply> pageForUser(Integer userId, String status, int page, int size) {
        ValidationUtils.require(userId != null, "用户不能为空");
        return page(userId, status, page, size);
    }

    @Override
    public PageResult<BorrowApply> pageForAdmin(String status, int page, int size) {
        return page(null, status, page, size);
    }

    @Override
    public DashboardStats dashboard() {
        DashboardStats stats = new DashboardStats();
        stats.setPendingApplyCount(borrowApplyMapper.countByStatus(Const.APPLY_STATUS_PENDING));
        stats.setBorrowedApplyCount(borrowApplyMapper.countByStatus(Const.APPLY_STATUS_BORROWED));
        stats.setTodayApplyCount(borrowApplyMapper.countToday());

        Map<String, Long> deviceCounts = new LinkedHashMap<>();
        deviceCounts.put(Const.DEVICE_STATUS_AVAILABLE, deviceMapper.countByStatus(Const.DEVICE_STATUS_AVAILABLE));
        deviceCounts.put(Const.DEVICE_STATUS_BORROWED, deviceMapper.countByStatus(Const.DEVICE_STATUS_BORROWED));
        deviceCounts.put(Const.DEVICE_STATUS_MAINTENANCE, deviceMapper.countByStatus(Const.DEVICE_STATUS_MAINTENANCE));
        deviceCounts.put(Const.DEVICE_STATUS_RETIRED, deviceMapper.countByStatus(Const.DEVICE_STATUS_RETIRED));
        stats.setDeviceStatusCounts(deviceCounts);
        return stats;
    }

    private PageResult<BorrowApply> page(Integer userId, String status, int page, int size) {
        validateStatusFilter(status);
        int safePage = Math.max(page, 1);
        int safeSize = Math.min(Math.max(size, 1), 50);
        int offset = (safePage - 1) * safeSize;
        long total = borrowApplyMapper.count(userId, emptyToNull(status));
        List<BorrowApply> list = borrowApplyMapper.page(userId, emptyToNull(status), offset, safeSize);
        return new PageResult<>(list, total, safePage, safeSize);
    }

    private Device validateApplyFields(Integer deviceId, LocalDate startDate, LocalDate endDate, String purposeType, String purposeNote) {
        ValidationUtils.require(deviceId != null, "设备ID不能为空");
        Device device = deviceMapper.selectById(deviceId);
        ValidationUtils.require(device != null, "设备不存在");
        ValidationUtils.require(Const.DEVICE_STATUS_AVAILABLE.equals(device.getStatus()), "设备状态必须为available");
        ValidationUtils.require(!Const.DEVICE_STATUS_RETIRED.equals(device.getStatus()), "设备已退役，不能借用");
        ValidationUtils.require(startDate != null, "计划借用开始日期不能为空");
        ValidationUtils.require(!startDate.isBefore(LocalDate.now()), "计划借用开始日期不能早于当前日期");
        ValidationUtils.require(endDate != null, "计划归还日期不能为空");
        ValidationUtils.require(endDate.isAfter(startDate), "计划归还日期必须晚于开始日期");
        ValidationUtils.require(isAllowedPurpose(purposeType), "借用用途只能是course/research/competition/other之一");
        if (Const.PURPOSE_OTHER.equals(purposeType)) {
            ValidationUtils.requireNotBlank(purposeNote, "用途为其他时必须填写用途说明");
        }
        if (purposeNote != null) {
            ValidationUtils.requireMaxLength(purposeNote, 500, "用途说明长度不能超过500字符");
        }
        return device;
    }

    private int calculateBorrowDays(LocalDate startDate, LocalDate endDate) {
        long days = ChronoUnit.DAYS.between(startDate, endDate);
        ValidationUtils.require(days > 0 && days <= Integer.MAX_VALUE, "借用天数不合法");
        return (int) days;
    }

    private void assertNoConflict(Integer deviceId, LocalDate startDate, LocalDate endDate, List<String> statuses, Integer excludeApplyId) {
        long conflict = borrowApplyMapper.countConflict(deviceId, startDate, endDate, statuses, excludeApplyId);
        ValidationUtils.require(conflict == 0, "该设备在所选时间段内已有借用申请或借出记录，不能重复申请");
    }

    private BorrowApply requireApply(Integer applyId) {
        ValidationUtils.require(applyId != null, "申请ID不能为空");
        BorrowApply apply = borrowApplyMapper.selectById(applyId);
        ValidationUtils.require(apply != null, "借用申请不存在");
        return apply;
    }

    private void requireStatus(BorrowApply apply, String required, String message) {
        if (!required.equals(apply.getStatus())) {
            throw new BizException(message);
        }
    }

    private void updateApplyStatus(Integer applyId, String status, Integer auditUserId, String auditNote,
                                   Date actualBorrowTime, Date actualReturnTime, String returnNote) {
        BorrowApply update = new BorrowApply();
        update.setApplyId(applyId);
        update.setStatus(status);
        update.setAuditUserId(auditUserId);
        if (auditUserId != null) {
            update.setAuditTime(new Date());
        }
        update.setAuditNote(auditNote);
        update.setActualBorrowTime(actualBorrowTime);
        update.setActualReturnTime(actualReturnTime);
        update.setReturnNote(returnNote);
        borrowApplyMapper.updateStatus(update);
    }

    private boolean isAllowedPurpose(String purposeType) {
        return Const.PURPOSE_COURSE.equals(purposeType)
                || Const.PURPOSE_RESEARCH.equals(purposeType)
                || Const.PURPOSE_COMPETITION.equals(purposeType)
                || Const.PURPOSE_OTHER.equals(purposeType);
    }

    private void validateStatusFilter(String status) {
        if (status == null || status.trim().isEmpty()) {
            return;
        }
        boolean valid = Const.APPLY_STATUS_PENDING.equals(status)
                || Const.APPLY_STATUS_APPROVED.equals(status)
                || Const.APPLY_STATUS_REJECTED.equals(status)
                || Const.APPLY_STATUS_BORROWED.equals(status)
                || Const.APPLY_STATUS_RETURNED.equals(status)
                || Const.APPLY_STATUS_CANCELLED.equals(status);
        ValidationUtils.require(valid, "申请状态筛选条件不合法");
    }

    private String trimToNull(String value) {
        if (value == null || value.trim().isEmpty()) {
            return null;
        }
        return value.trim();
    }

    private String emptyToNull(String value) {
        return value == null || value.trim().isEmpty() ? null : value.trim();
    }
}
