package com.lab.borrow.web.interceptor;

import com.lab.borrow.domain.Const;
import org.springframework.web.servlet.HandlerInterceptor;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class AuthInterceptor implements HandlerInterceptor {
    @Override
    public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
        Object user = request.getSession().getAttribute(Const.SESSION_USER);
        if (user != null) {
            return true;
        }

        if (isJsonRequest(request)) {
            response.setCharacterEncoding("UTF-8");
            response.setContentType("application/json;charset=UTF-8");
            response.getWriter().write("{\"code\":400,\"message\":\"未登录\",\"data\":null}");
            return false;
        }

        response.sendRedirect(request.getContextPath() + "/auth/login");
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
