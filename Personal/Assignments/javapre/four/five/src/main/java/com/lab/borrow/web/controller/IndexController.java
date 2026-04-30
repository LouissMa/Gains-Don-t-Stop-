package com.lab.borrow.web.controller;

import com.lab.borrow.domain.Const;
import com.lab.borrow.entity.User;
import com.lab.borrow.service.BorrowApplyService;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;

import javax.annotation.Resource;
import javax.servlet.http.HttpServletRequest;

@Controller
public class IndexController {
    @Resource
    private BorrowApplyService borrowApplyService;

    @GetMapping("/")
    public String index(HttpServletRequest request) {
        Object obj = request.getSession().getAttribute(Const.SESSION_USER);
        if (obj instanceof User && Const.ROLE_ADMIN.equals(((User) obj).getRole())) {
            request.setAttribute("stats", borrowApplyService.dashboard());
            return "dashboard";
        }
        return "redirect:/devices";
    }
}
