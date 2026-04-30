package com.lab.borrow.web.api;

import com.lab.borrow.common.PageResult;
import com.lab.borrow.common.Result;
import com.lab.borrow.domain.Const;
import com.lab.borrow.entity.BorrowApply;
import com.lab.borrow.entity.DashboardStats;
import com.lab.borrow.entity.User;
import com.lab.borrow.service.BorrowApplyService;
import com.lab.borrow.web.dto.BorrowApplyForm;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import javax.annotation.Resource;
import javax.servlet.http.HttpSession;
import javax.validation.Valid;

@RestController
@RequestMapping("/api/borrows")
public class BorrowApplyApiController {
    @Resource
    private BorrowApplyService borrowApplyService;

    @PostMapping
    public Result<BorrowApply> submit(@Valid @RequestBody BorrowApplyForm form, HttpSession session) {
        User user = (User) session.getAttribute(Const.SESSION_USER);
        return Result.success(borrowApplyService.submit(user.getUserId(), form.getDeviceId(), form.getStartDate(), form.getEndDate(), form.getPurposeType(), form.getPurposeNote()));
    }

    @GetMapping("/my")
    public Result<PageResult<BorrowApply>> my(@RequestParam(value = "status", required = false) String status,
                                              @RequestParam(value = "page", defaultValue = "1") int page,
                                              @RequestParam(value = "size", defaultValue = "10") int size,
                                              HttpSession session) {
        User user = (User) session.getAttribute(Const.SESSION_USER);
        return Result.success(borrowApplyService.pageForUser(user.getUserId(), status, page, size));
    }

    @GetMapping("/admin")
    public Result<PageResult<BorrowApply>> admin(@RequestParam(value = "status", required = false) String status,
                                                 @RequestParam(value = "page", defaultValue = "1") int page,
                                                 @RequestParam(value = "size", defaultValue = "10") int size) {
        return Result.success(borrowApplyService.pageForAdmin(status, page, size));
    }

    @PostMapping("/{applyId}/approve")
    public Result<Void> approve(@PathVariable("applyId") Integer applyId,
                                @RequestParam(value = "auditNote", required = false) String auditNote,
                                HttpSession session) {
        borrowApplyService.approve(applyId, currentUserId(session), auditNote);
        return Result.success(null);
    }

    @PostMapping("/{applyId}/reject")
    public Result<Void> reject(@PathVariable("applyId") Integer applyId,
                               @RequestParam String auditNote,
                               HttpSession session) {
        borrowApplyService.reject(applyId, currentUserId(session), auditNote);
        return Result.success(null);
    }

    @PostMapping("/{applyId}/borrow")
    public Result<Void> confirmBorrow(@PathVariable("applyId") Integer applyId, HttpSession session) {
        borrowApplyService.confirmBorrow(applyId, currentUserId(session));
        return Result.success(null);
    }

    @PostMapping("/{applyId}/return")
    public Result<Void> confirmReturn(@PathVariable("applyId") Integer applyId,
                                      @RequestParam String returnNote,
                                      HttpSession session) {
        borrowApplyService.confirmReturn(applyId, currentUserId(session), returnNote);
        return Result.success(null);
    }

    @PostMapping("/{applyId}/cancel")
    public Result<Void> cancel(@PathVariable("applyId") Integer applyId, HttpSession session) {
        User user = (User) session.getAttribute(Const.SESSION_USER);
        borrowApplyService.cancel(applyId, user.getUserId());
        return Result.success(null);
    }

    @GetMapping("/dashboard")
    public Result<DashboardStats> dashboard() {
        return Result.success(borrowApplyService.dashboard());
    }

    private Integer currentUserId(HttpSession session) {
        User user = (User) session.getAttribute(Const.SESSION_USER);
        return user.getUserId();
    }
}
