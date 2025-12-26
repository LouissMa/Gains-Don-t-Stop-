<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="jakarta.tags.core" %>
<!DOCTYPE html>
<html>
<head>
    <title>登录 - 宠物商城</title>
    <link rel="stylesheet" href="${pageContext.request.contextPath}/css/style.css">
    <link rel="icon" href="${pageContext.request.contextPath}/images/favicon.ico" type="image/x-icon">
</head>
<body class="auth-body">

<div class="auth-container">
    <div style="text-align: center; margin-bottom: 20px;">
        <a href="home">
            <img src="${pageContext.request.contextPath}/images/logo.png" alt="宠物商城" style="height: 60px;">
        </a>
    </div>
    <h2 class="auth-title">欢迎回来</h2>
    
    <c:if test="${not empty error}">
        <div style="color: #ff4d4f; text-align: center; margin-bottom: 20px; background: #fff1f0; padding: 10px; border-radius: 4px; border: 1px solid #ffccc7;">
            ${error}
        </div>
    </c:if>
    <c:if test="${param.registered}">
        <div style="color: #52c41a; text-align: center; margin-bottom: 20px; background: #f6ffed; padding: 10px; border-radius: 4px; border: 1px solid #b7eb8f;">
            注册成功！请登录。
        </div>
    </c:if>
    
    <form action="login" method="post">
        <div class="form-group">
            <label>用户名</label>
            <input type="text" name="username" required placeholder="请输入您的用户名">
        </div>
        <div class="form-group">
            <label>密码</label>
            <input type="password" name="password" required placeholder="请输入您的密码">
        </div>
        <button type="submit" class="btn btn-primary" style="width: 100%; margin-top: 10px; padding: 12px;">立即登录</button>
    </form>
    
    <div style="text-align: center; margin-top: 20px; font-size: 14px;">
        还没有账号？ <a href="register" style="color: var(--primary-color); font-weight: bold;">免费注册</a>
    </div>
    <div style="text-align: center; margin-top: 10px;">
        <a href="home" style="color: #999; font-size: 12px;">返回首页</a>
    </div>
</div>

</body>
</html>
