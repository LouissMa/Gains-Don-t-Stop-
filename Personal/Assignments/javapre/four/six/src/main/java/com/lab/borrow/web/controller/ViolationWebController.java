package com.lab.borrow.web.controller;

import com.lab.borrow.common.PageResult;
import com.lab.borrow.domain.Const;
import com.lab.borrow.entity.BorrowApply;
import com.lab.borrow.entity.Device;
import com.lab.borrow.entity.OverdueItem;
import com.lab.borrow.entity.User;
import com.lab.borrow.entity.Violation;
import com.lab.borrow.entity.ViolationStat;
import com.lab.borrow.mapper.BorrowApplyMapper;
import com.lab.borrow.mapper.ViolationMapper;
import com.lab.borrow.service.DeviceService;
import com.lab.borrow.service.ViolationService;
import org.springframework.format.annotation.DateTimeFormat;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;

import javax.servlet.http.HttpServletRequest;
import java.time.LocalDate;
import java.time.temporal.ChronoUnit;
import java.util.ArrayList;
import java.util.List;

@Controller
public class ViolationWebController {
    private final ViolationService violationService;
    private final DeviceService deviceService;
    private final BorrowApplyMapper borrowApplyMapper;
    private final ViolationMapper violationMapper;

    public ViolationWebController(ViolationService violationService, DeviceService deviceService, BorrowApplyMapper borrowApplyMapper, ViolationMapper violationMapper) {
        this.violationService = violationService;
        this.deviceService = deviceService;
        this.borrowApplyMapper = borrowApplyMapper;
        this.violationMapper = violationMapper;
    }

    @GetMapping("/violations")
    public String myViolations(@RequestParam(value = "status", required = false) String status,
                               @RequestParam(value = "page", required = false, defaultValue = "1") int page,
                               @RequestParam(value = "size", required = false, defaultValue = "10") int size,
                               HttpServletRequest request) {
        violationService.detectOverdue();
        User me = currentUser(request);
        PageResult<Violation> violationPage = violationService.pageForUser(me.getUserId(), status, page, size);
        request.setAttribute("violationPage", violationPage);
        request.setAttribute("status", status == null ? "" : status);
        request.setAttribute("statuses", statuses());
        return "violation_my";
    }

    @GetMapping("/admin/violations")
    public String adminList(@RequestParam(value = "userId", required = false) Integer userId,
                            @RequestParam(value = "deviceId", required = false) Integer deviceId,
                            @RequestParam(value = "status", required = false) String status,
                            @RequestParam(value = "page", required = false, defaultValue = "1") int page,
                            @RequestParam(value = "size", required = false, defaultValue = "10") int size,
                            HttpServletRequest request) {
        violationService.detectOverdue();
        PageResult<Violation> violationPage = violationService.pageForAdmin(userId, deviceId, status, page, size);
        request.setAttribute("violationPage", violationPage);
        request.setAttribute("userId", userId);
        request.setAttribute("deviceId", deviceId);
        request.setAttribute("status", status == null ? "" : status);
        request.setAttribute("statuses", statuses());
        return "violation_list";
    }

    @GetMapping("/admin/violations/{id}")
    public String adminDetail(@PathVariable("id") Integer id, HttpServletRequest request) {
        violationService.detectOverdue();
        Violation v = violationService.getById(id);
        request.setAttribute("v", v);
        return "violation_detail";
    }

    @PostMapping("/admin/violations/{id}/process")
    public String process(@PathVariable("id") Integer id,
                          @RequestParam("processNote") String processNote,
                          HttpServletRequest request) {
        User admin = currentUser(request);
        violationService.process(id, admin.getUserId(), processNote);
        return "redirect:/admin/violations/" + id;
    }

    @GetMapping("/admin/violations/stats")
    public String stats(HttpServletRequest request) {
        List<ViolationStat> userStats = violationService.statsByUser();
        List<ViolationStat> deviceStats = violationService.statsByDevice();
        request.setAttribute("userStats", userStats);
        request.setAttribute("deviceStats", deviceStats);
        return "violation_stats";
    }

    @GetMapping("/admin/overdue")
    public String overdue(HttpServletRequest request) {
        violationService.detectOverdue();
        LocalDate today = LocalDate.now();
        List<BorrowApply> applies = borrowApplyMapper.listOverdueBorrowed(today);
        List<OverdueItem> items = new ArrayList<>();
        for (BorrowApply apply : applies) {
            OverdueItem item = new OverdueItem();
            item.setApply(apply);
            long days = ChronoUnit.DAYS.between(apply.getEndDate(), today);
            item.setOverdueDays(Math.max(days, 0));
            Violation v = violationMapper.selectByBorrowRecordId(apply.getApplyId());
            item.setViolationId(v == null ? null : v.getViolationId());
            items.add(item);
        }
        request.setAttribute("items", items);
        return "overdue_list";
    }

    @GetMapping("/admin/usage")
    public String usage(@RequestParam(value = "deviceId", required = false) Integer deviceId,
                        @RequestParam(value = "startDate", required = false) @DateTimeFormat(pattern = "yyyy-MM-dd") LocalDate startDate,
                        @RequestParam(value = "endDate", required = false) @DateTimeFormat(pattern = "yyyy-MM-dd") LocalDate endDate,
                        HttpServletRequest request) {
        List<Device> devices = deviceService.page(null, null, 1, 200).getList();
        request.setAttribute("devices", devices);
        request.setAttribute("deviceId", deviceId);
        request.setAttribute("startDate", startDate);
        request.setAttribute("endDate", endDate);

        if (deviceId != null && startDate != null && endDate != null) {
            ViolationService.DeviceUsageRate rate = violationService.usageRate(deviceId, startDate, endDate);
            request.setAttribute("rate", rate);
        }
        return "usage_rate";
    }

    private User currentUser(HttpServletRequest request) {
        return (User) request.getSession().getAttribute(Const.SESSION_USER);
    }

    private String[] statuses() {
        return new String[]{Const.VIOLATION_STATUS_UNTREATED, Const.VIOLATION_STATUS_PROCESSED};
    }
}
