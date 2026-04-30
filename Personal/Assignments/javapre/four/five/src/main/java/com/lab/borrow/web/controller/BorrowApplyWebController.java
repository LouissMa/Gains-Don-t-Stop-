package com.lab.borrow.web.controller;

import com.lab.borrow.common.PageResult;
import com.lab.borrow.domain.Const;
import com.lab.borrow.entity.BorrowApply;
import com.lab.borrow.entity.Device;
import com.lab.borrow.entity.User;
import com.lab.borrow.service.BorrowApplyService;
import com.lab.borrow.service.DeviceService;
import com.lab.borrow.web.dto.BorrowApplyForm;
import org.springframework.stereotype.Controller;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;

import javax.annotation.Resource;
import javax.servlet.http.HttpServletRequest;
import javax.validation.Valid;

@Controller
public class BorrowApplyWebController {
    @Resource
    private BorrowApplyService borrowApplyService;

    @Resource
    private DeviceService deviceService;

    @GetMapping("/devices/{deviceId}/apply")
    public String applyForm(@PathVariable("deviceId") Integer deviceId, HttpServletRequest request) {
        Device device = deviceService.getById(deviceId);
        BorrowApplyForm form = new BorrowApplyForm();
        form.setDeviceId(deviceId);
        request.setAttribute("device", device);
        request.setAttribute("form", form);
        request.setAttribute("purposes", purposes());
        return "borrow_apply_form";
    }

    @PostMapping("/borrows")
    public String submit(@Valid BorrowApplyForm form, BindingResult bindingResult, HttpServletRequest request) {
        User user = currentUser(request);
        if (bindingResult.hasErrors()) {
            request.setAttribute("message", bindingResult.getFieldError() == null ? "参数错误" : bindingResult.getFieldError().getDefaultMessage());
            request.setAttribute("device", deviceService.getById(form.getDeviceId()));
            request.setAttribute("form", form);
            request.setAttribute("purposes", purposes());
            return "borrow_apply_form";
        }
        borrowApplyService.submit(user.getUserId(), form.getDeviceId(), form.getStartDate(), form.getEndDate(), form.getPurposeType(), form.getPurposeNote());
        return "redirect:/my/borrows";
    }

    @GetMapping("/my/borrows")
    public String myList(@RequestParam(value = "status", required = false) String status,
                         @RequestParam(value = "page", required = false, defaultValue = "1") int page,
                         @RequestParam(value = "size", required = false, defaultValue = "10") int size,
                         HttpServletRequest request) {
        User user = currentUser(request);
        PageResult<BorrowApply> applyPage = borrowApplyService.pageForUser(user.getUserId(), status, page, size);
        request.setAttribute("applyPage", applyPage);
        request.setAttribute("status", status == null ? "" : status);
        request.setAttribute("statuses", statuses());
        request.setAttribute("adminView", false);
        return "borrow_list";
    }

    @GetMapping("/borrows/{applyId}")
    public String detail(@PathVariable("applyId") Integer applyId, HttpServletRequest request) {
        BorrowApply apply = borrowApplyService.getById(applyId);
        User user = currentUser(request);
        if (!Const.ROLE_ADMIN.equals(user.getRole()) && !apply.getUserId().equals(user.getUserId())) {
            request.setAttribute("message", "无权限查看该申请");
            request.setAttribute("path", request.getRequestURI());
            return "error";
        }
        request.setAttribute("apply", apply);
        return "borrow_detail";
    }

    @PostMapping("/my/borrows/{applyId}/cancel")
    public String cancel(@PathVariable("applyId") Integer applyId, HttpServletRequest request) {
        borrowApplyService.cancel(applyId, currentUser(request).getUserId());
        return "redirect:/my/borrows";
    }

    @GetMapping("/admin/borrows")
    public String adminList(@RequestParam(value = "status", required = false) String status,
                            @RequestParam(value = "page", required = false, defaultValue = "1") int page,
                            @RequestParam(value = "size", required = false, defaultValue = "10") int size,
                            HttpServletRequest request) {
        PageResult<BorrowApply> applyPage = borrowApplyService.pageForAdmin(status, page, size);
        request.setAttribute("applyPage", applyPage);
        request.setAttribute("status", status == null ? "" : status);
        request.setAttribute("statuses", statuses());
        request.setAttribute("adminView", true);
        return "borrow_list";
    }

    @PostMapping("/admin/borrows/{applyId}/approve")
    public String approve(@PathVariable("applyId") Integer applyId,
                          @RequestParam(value = "auditNote", required = false) String auditNote,
                          HttpServletRequest request) {
        borrowApplyService.approve(applyId, currentUser(request).getUserId(), auditNote);
        return "redirect:/admin/borrows";
    }

    @PostMapping("/admin/borrows/{applyId}/reject")
    public String reject(@PathVariable("applyId") Integer applyId,
                         @RequestParam("auditNote") String auditNote,
                         HttpServletRequest request) {
        borrowApplyService.reject(applyId, currentUser(request).getUserId(), auditNote);
        return "redirect:/admin/borrows";
    }

    @PostMapping("/admin/borrows/{applyId}/borrow")
    public String confirmBorrow(@PathVariable("applyId") Integer applyId, HttpServletRequest request) {
        borrowApplyService.confirmBorrow(applyId, currentUser(request).getUserId());
        return "redirect:/admin/borrows";
    }

    @PostMapping("/admin/borrows/{applyId}/return")
    public String confirmReturn(@PathVariable("applyId") Integer applyId,
                                @RequestParam("returnNote") String returnNote,
                                HttpServletRequest request) {
        borrowApplyService.confirmReturn(applyId, currentUser(request).getUserId(), returnNote);
        return "redirect:/admin/borrows";
    }

    private User currentUser(HttpServletRequest request) {
        return (User) request.getSession().getAttribute(Const.SESSION_USER);
    }

    private String[] statuses() {
        return new String[]{
                Const.APPLY_STATUS_PENDING,
                Const.APPLY_STATUS_APPROVED,
                Const.APPLY_STATUS_REJECTED,
                Const.APPLY_STATUS_BORROWED,
                Const.APPLY_STATUS_RETURNED,
                Const.APPLY_STATUS_CANCELLED
        };
    }

    private String[] purposes() {
        return new String[]{Const.PURPOSE_COURSE, Const.PURPOSE_RESEARCH, Const.PURPOSE_COMPETITION, Const.PURPOSE_OTHER};
    }
}
