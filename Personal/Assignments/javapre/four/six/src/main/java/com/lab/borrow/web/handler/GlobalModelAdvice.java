package com.lab.borrow.web.handler;

import com.lab.borrow.domain.Const;
import com.lab.borrow.entity.User;
import com.lab.borrow.service.ViolationService;
import org.springframework.web.bind.annotation.ControllerAdvice;
import org.springframework.web.bind.annotation.ModelAttribute;

import javax.servlet.http.HttpServletRequest;

@ControllerAdvice(basePackages = "com.lab.borrow.web.controller")
public class GlobalModelAdvice {
    private final ViolationService violationService;

    public GlobalModelAdvice(ViolationService violationService) {
        this.violationService = violationService;
    }

    @ModelAttribute("untreatedViolationCount")
    public Long untreatedViolationCount(HttpServletRequest request) {
        Object obj = request.getSession().getAttribute(Const.SESSION_USER);
        if (!(obj instanceof User)) {
            return 0L;
        }
        User user = (User) obj;
        long count = violationService.countUntreatedByUserId(user.getUserId());
        request.getSession().setAttribute(Const.SESSION_UNTREATED_VIOLATION_COUNT, count);
        return count;
    }
}
