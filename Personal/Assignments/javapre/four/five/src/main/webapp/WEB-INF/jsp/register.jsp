<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@ include file="/WEB-INF/jsp/_base.jspf" %>
<!DOCTYPE html>
<html>
<head>
    <title>注册</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet">
</head>
<body class="bg-light">
<div class="container" style="max-width: 680px; margin-top: 60px;">
    <div class="card shadow-sm">
        <div class="card-body p-4">
            <h4 class="mb-3">用户注册</h4>
            <c:if test="${not empty message}">
                <div class="alert alert-danger">${message}</div>
            </c:if>
            <form method="post" action="${ctx}/auth/register">
                <div class="row">
                    <div class="col-md-6 mb-3">
                        <label class="form-label">用户名</label>
                        <input class="form-control" name="username" value="${form.username}" required>
                        <div class="form-text">4~50位，字母/数字/下划线</div>
                    </div>
                    <div class="col-md-6 mb-3">
                        <label class="form-label">密码</label>
                        <input type="password" class="form-control" name="password" required>
                        <div class="form-text">6~20位</div>
                    </div>
                </div>
                <div class="row">
                    <div class="col-md-6 mb-3">
                        <label class="form-label">真实姓名</label>
                        <input class="form-control" name="realName" value="${form.realName}" required>
                    </div>
                    <div class="col-md-6 mb-3">
                        <label class="form-label">学号/工号</label>
                        <input class="form-control" name="studentNo" value="${form.studentNo}" required>
                    </div>
                </div>
                <div class="row">
                    <div class="col-md-6 mb-3">
                        <label class="form-label">手机号</label>
                        <input class="form-control" name="phone" value="${form.phone}">
                    </div>
                    <div class="col-md-6 mb-3">
                        <label class="form-label">邮箱</label>
                        <input class="form-control" name="email" value="${form.email}">
                    </div>
                </div>
                <div class="d-grid gap-2">
                    <button class="btn btn-primary" type="submit">注册并登录</button>
                    <a class="btn btn-outline-secondary" href="${ctx}/auth/login">返回登录</a>
                </div>
            </form>
        </div>
    </div>
</div>
<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js"></script>
</body>
</html>
