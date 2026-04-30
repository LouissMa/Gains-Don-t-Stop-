package com.lab.borrow.web.interceptor;

import com.lab.borrow.domain.Const;
import com.lab.borrow.entity.User;
import org.springframework.web.servlet.HandlerInterceptor;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class AdminInterceptor implements HandlerInterceptor {
    @Override
    public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
        Object obj = request.getSession().getAttribute(Const.SESSION_USER);
        if (!(obj instanceof User)) {
            response.sendRedirect(request.getContextPath() + "/auth/login");
            return false;
        }
        User user = (User) obj;
        if (Const.ROLE_ADMIN.equals(user.getRole())) {
            return true;
        }

        if (isJsonRequest(request)) {
            response.setCharacterEncoding("UTF-8");
            response.setContentType("application/json;charset=UTF-8");
            response.getWriter().write("{\"code\":400,\"message\":\"无权限\",\"data\":null}");
            return false;
        }

        response.sendRedirect(request.getContextPath() + "/error?msg=无权限");
        return false;
    }

    private boolean isJsonRequest(HttpServletRequest request) {
        String accept = request.getHeader("Accept");
        if (accept != null && accept.contains("application/json")) {
            return true;
        }
        String xrw = request.getHeader("X-Requested-With");
        return xrw != null && xrw.contains("XMLHttpRequest");
    }
}
