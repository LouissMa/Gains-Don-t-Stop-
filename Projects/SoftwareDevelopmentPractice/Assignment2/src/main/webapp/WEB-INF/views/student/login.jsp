<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="form" uri="http://www.springframework.org/tags/form" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<!DOCTYPE html>
<html lang="zh-CN">
<head>
    <meta charset="UTF-8">
    <title>用户登录 - 校园生活服务系统</title>
    <link rel="stylesheet" href="${pageContext.request.contextPath}/static/css/style.css">
    <style>
        body {
            background: linear-gradient(135deg, #3498db, #2c3e50);
            height: 100vh;
            display: flex;
            align-items: center;
            justify-content: center;
        }
        .login-card {
            width: 100%;
            max-width: 400px;
            background: var(--white);
            padding: 40px;
            border-radius: var(--border-radius);
            box-shadow: 0 15px 35px rgba(0,0,0,0.2);
        }
        .login-header { text-align: center; margin-bottom: 30px; }
        .login-header h2 { color: var(--secondary-color); margin-bottom: 10px; }
        .login-header p { color: var(--dark-gray); font-size: 0.9rem; }
        .error-msg {
            background: #fff5f5;
            color: var(--accent-color);
            padding: 10px;
            border-radius: 4px;
            margin-bottom: 20px;
            font-size: 0.9rem;
            text-align: center;
            border: 1px solid #fed7d7;
        }
    </style>
</head>
<body>
    <div class="login-card">
        <div class="login-header">
            <h2>欢迎回来</h2>
            <p>登录您的校园生活服务系统账号</p>
        </div>

        <c:if test="${not empty error}">
            <div class="error-msg">${error}</div>
        </c:if>

        <form action="${pageContext.request.contextPath}/student/login" method="post">
            <div class="form-group">
                <label class="form-label">学号</label>
                <input type="text" name="studentId" class="form-control" placeholder="请输入学号" required>
            </div>
            <div class="form-group">
                <label class="form-label">密码</label>
                <input type="password" name="password" class="form-control" placeholder="请输入密码" required>
            </div>
            <button type="submit" class="btn btn-primary" style="width: 100%; padding: 12px; margin-top: 10px; font-size: 1rem;">立即登录</button>
        </form>

        <div style="text-align: center; margin-top: 25px; font-size: 0.9rem; color: var(--dark-gray);">
            还没有账号？ <a href="${pageContext.request.contextPath}/student/toRegister" style="color: var(--primary-color); font-weight: 600; text-decoration: none;">立即注册</a>
        </div>
        <div style="text-align: center; margin-top: 15px;">
            <a href="${pageContext.request.contextPath}/index.jsp" style="color: var(--dark-gray); text-decoration: none; font-size: 0.85rem;">← 返回首页</a>
        </div>
    </div>
</body>
</html>
