package com.lab.borrow.config;

import com.lab.borrow.web.interceptor.AdminInterceptor;
import com.lab.borrow.web.interceptor.AuthInterceptor;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.servlet.config.annotation.InterceptorRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;

@Configuration
public class WebMvcConfig implements WebMvcConfigurer {
    @Override
    public void addInterceptors(InterceptorRegistry registry) {
        registry.addInterceptor(new AdminInterceptor())
                .addPathPatterns(
                        "/admin/**",
                        "/api/borrows/admin",
                        "/api/borrows/dashboard",
                        "/api/borrows/*/approve",
                        "/api/borrows/*/reject",
                        "/api/borrows/*/borrow",
                        "/api/borrows/*/return")
                .excludePathPatterns("/auth/**");

        registry.addInterceptor(new AuthInterceptor())
                .addPathPatterns("/**")
                .excludePathPatterns("/auth/**", "/static/**", "/error");
    }
}
